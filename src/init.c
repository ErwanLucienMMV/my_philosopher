/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaigne <emaigne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 16:30:17 by emaigne           #+#    #+#             */
/*   Updated: 2026/03/16 17:23:13 by emaigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	assign_forks(t_table *table, int i)
{
	int	n;

	n = table->args.number_of_philo;
	table->philos[i].left_fork = &table->forks[i];
	table->philos[i].right_fork = &table->forks[(i + 1) % n];
}

int	init_mutexes(t_table *table)
{
	int	i;
	int	n;

	n = table->args.number_of_philo;
	table->forks = malloc(sizeof(pthread_mutex_t) * n);
	if (!table->forks)
		return (1);
	i = 0;
	while (i < n)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&table->forks[i]);
			free(table->forks);
			return (1);
		}
		i++;
	}
	if (pthread_mutex_init(&table->print_mutex, NULL) != 0
		|| pthread_mutex_init(&table->stop_mutex, NULL) != 0)
		return (1);
	table->stop_simulation = 0;
	return (0);
}

int	init_philo(t_table *table, int i)
{
	t_philo	*philo;

	philo = &table->philos[i];
	philo->id = i + 1;
	philo->last_meal = 0;
	philo->meals_eaten = 0;
	philo->table = table;
	if (pthread_mutex_init(&philo->meal_mutex, NULL) != 0)
		return (1);
	assign_forks(table, i);
	return (0);
}

int	initialize_philo(t_table *table)
{
	int	i;
	int	n;

	n = table->args.number_of_philo;
	table->philos = malloc(sizeof(t_philo) * n);
	if (!table->philos)
		return (1);
	i = 0;
	while (i < n)
	{
		if (init_philo(table, i))
		{
			while (--i >= 0)
				pthread_mutex_destroy(&(table->philos[i].meal_mutex));
			free(table->philos);
			return (1);
		}
		i++;
	}
	return (0);
}
