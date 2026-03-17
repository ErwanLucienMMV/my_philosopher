/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_helpers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaigne <emaigne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 17:04:59 by emaigne           #+#    #+#             */
/*   Updated: 2026/03/17 19:43:18 by emaigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	start_simulation(t_table *table)
{
	int	i;

	table->start_time = get_time();
	i = 0;
	while (i < table->args.number_of_philo)
	{
		pthread_mutex_lock(&table->philos[i].meal_mutex);
		table->philos[i].last_meal = table->start_time;
		pthread_mutex_unlock(&table->philos[i].meal_mutex);
		if (pthread_create(&table->philos[i].thread,
				NULL, philo_routine, &table->philos[i]) != 0)
			return (1);
		i++;
	}
	if (pthread_create(&table->monitor, NULL,
			monitor_routine, table) != 0)
		return (1);
	return (0);
}

void	wait_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->args.number_of_philo)
	{
		pthread_join(table->philos[i].thread, NULL);
		i++;
	}
	pthread_join(table->monitor, NULL);
}

int	simulation_stopped(t_table *table)
{
	int	stop;

	pthread_mutex_lock(&table->stop_mutex);
	stop = table->stop_simulation;
	pthread_mutex_unlock(&table->stop_mutex);
	return (stop);
}

void	print_status(t_philo *philo, char *msg)
{
	long	time;

	pthread_mutex_lock(&philo->table->print_mutex);
	if (!simulation_stopped(philo->table))
	{
		time = get_time() - philo->table->start_time;
		printf("%ld %d %s\n", time, philo->id, msg);
	}
	pthread_mutex_unlock(&philo->table->print_mutex);
}

void	smart_sleep(long time, t_table *table)
{
	long	start;

	start = get_time();
	while (!simulation_stopped(table))
	{
		if (get_time() - start >= time)
			break ;
		usleep(500);
	}
}
