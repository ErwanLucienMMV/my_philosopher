/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaigne <emaigne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 14:15:13 by emaigne           #+#    #+#             */
/*   Updated: 2026/03/16 15:31:56 by emaigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	assign_forks(t_table *table, int i)
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

static int	init_philo(t_table *table, int i)
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

t_philo	*initialize_philo(t_table *table)
{
	int	i;
	int	n;

	n = table->args.number_of_philo;
	table->philos = malloc(sizeof(t_philo) * n);
	if (!table->philos)
		return (NULL);
	i = 0;
	while (i < n)
	{
		if (init_philo(table, i))
			return (free(table->philos), NULL);
		i++;
	}
	return (table->philos);
}

int	main(int argc, char **argv)
{
	t_args	args;
	t_table	table;

	if (parse_args(argc, argv, &args))
		return (1);
	table.args = args;
	table.philos = initialize_philo(&table);
	if (!table.philos)
		return (1);
	if (!init_mutexes(&table))
	{
		table.start_time = get_time();
	}
	return (free(table.philos), 0);
}
