/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaigne <emaigne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 14:14:03 by emaigne           #+#    #+#             */
/*   Updated: 2026/03/16 15:42:21 by emaigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

/**
 * Checks that a string is only a number, and fitting integer size
 * return 1 if it is valid 0 otherwise
 */
int	ft_is_intnum(char *str)
{
	int	i;
	int	digit_count;

	if (!str || !*str)
		return (0);
	i = 0;
	digit_count = 0;
	if (str[0] == '-' || str[0] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		digit_count++;
		i++;
	}
	if (digit_count > 10)
		return (0);
	return (1);
}

/**
 * Convert a string into an int
 */
int	ft_atoi(const char *str)
{
	int	i;
	int	nbr;
	int	sign;

	nbr = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || ('\t' <= str[i] && str[i] <= '\r'))
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		sign *= -1;
		i++;
	}
	while ('0' <= str[i] && str[i] <= '9')
	{
		nbr = nbr * 10 + str[i] - '0';
		i++;
	}
	return (nbr * sign);
}

/**
 * Transform the struct return by gettimeofday into 
 * usable number of ms since EPOCH
 */
long	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
		return (-1);
	return ((tv.tv_sec * 1000L) + (tv.tv_usec / 1000L));
}

/** Take the start time and return the time that passed
 * Usage: For the logs to get the ms
 */
long	time_since_start(t_table *table)
{
	return (get_time() - table->start_time);
}

/** Lock the mutex before checking the time as to avoid datarace
 * Calculate the time since the last meal and returns it
 * Usage: Having an easy to access value to compare against
 * time before dying
 */
long	time_since_last_meal(t_philo *philo)
{
	long	last_meal;
	long	now;

	pthread_mutex_lock(&philo->meal_mutex);
	last_meal = philo->last_meal;
	pthread_mutex_unlock(&philo->meal_mutex);
	now = get_time();
	return (now - last_meal);
}
