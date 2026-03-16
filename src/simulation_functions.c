/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_functions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaigne <emaigne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 16:59:11 by emaigne           #+#    #+#             */
/*   Updated: 2026/03/16 17:43:43 by emaigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork");
	}
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;

	if (philo->table->args.number_of_philo == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork");
		usleep(philo->table->args.time_to_die * 1000);
		pthread_mutex_unlock(philo->left_fork);
		return (NULL);
	}

	if (philo->id % 2 == 0)
		usleep(1000);

	while (!simulation_stopped(philo->table))
	{
		take_forks(philo);
		pthread_mutex_lock(&philo->meal_mutex);
		philo->last_meal = get_time();
		pthread_mutex_unlock(&philo->meal_mutex);
		print_status(philo, "is eating");
		usleep(philo->table->args.time_to_eat * 1000);
		philo->meals_eaten++;
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		print_status(philo, "is sleeping");
		usleep(philo->table->args.time_to_sleep * 1000);
		print_status(philo, "is thinking");
	}
	return (NULL);
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
			{
				pthread_mutex_lock(&table->print_mutex);
				printf("%ld %d died\n",
					get_time() - table->start_time,
					table->philos[i].id);
				pthread_mutex_unlock(&table->print_mutex);

				pthread_mutex_lock(&table->stop_mutex);
				table->stop_simulation = 1;
				pthread_mutex_unlock(&table->stop_mutex);

				return (NULL);
			}
			i++;
		}
		usleep(10);
	}
	return (NULL);
}
