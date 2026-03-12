/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaigne <emaigne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 14:15:13 by emaigne           #+#    #+#             */
/*   Updated: 2026/03/12 01:13:32 by emaigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

#include "philo.h"

static void	assign_forks(t_table *table, int i)
{
	int	n;

	n = table->args.number_of_philo;
	table->philos[i].left_fork = &table->forks[i];
	table->philos[i].right_fork = &table->forks[(i + 1) % n];
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
			return (NULL);
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
	return (0);
}
