/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_ripper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaigne <emaigne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 17:52:43 by emaigne           #+#    #+#             */
/*   Updated: 2026/03/17 19:59:14 by emaigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	are_all_philos_full(t_table *table)
{
	int		i;
	int		full;
	t_philo	*philo;

	if (table->args.number_of_times_eat <= 0)
		return (0);
	i = 0;
	while (i < table->args.number_of_philo)
	{
		philo = &table->philos[i];
		pthread_mutex_lock(&philo->meal_mutex);
		if (philo->meals_eaten < table->args.number_of_times_eat)
			full = 0;
		else
			full = 1;
		pthread_mutex_unlock(&philo->meal_mutex);
		if (!full)
			return (0);
		i++;
	}
	return (1);
}

void	threads_crow(t_table *table, int i)
{
	pthread_mutex_lock(&table->print_mutex);
	printf("%ld %d died\n", get_time() - table->start_time,
		table->philos[i].id);
	pthread_mutex_unlock(&table->print_mutex);
	pthread_mutex_lock(&table->stop_mutex);
	table->stop_simulation = 1;
	pthread_mutex_unlock(&table->stop_mutex);
}

int	is_it_gargantua(t_table *table)
{
	if (are_all_philos_full(table))
	{
		pthread_mutex_lock(&table->stop_mutex);
		table->stop_simulation = 1;
		pthread_mutex_unlock(&table->stop_mutex);
		return (1);
	}
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_table	*table;
	int		i;

	table = (t_table *)arg;
	while (!simulation_stopped(table))
	{
		i = 0;
		while (i < table->args.number_of_philo)
		{
			if (time_since_last_meal(&table->philos[i])
				> table->args.time_to_die)
				return (threads_crow(table, i), NULL);
			i++;
		}
		if (is_it_gargantua(table))
			return (NULL);
		usleep(10);
	}
	return (NULL);
}
