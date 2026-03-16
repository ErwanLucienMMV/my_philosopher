/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_argument.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaigne <emaigne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 13:48:39 by emaigne           #+#    #+#             */
/*   Updated: 2026/03/16 15:30:54 by emaigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

/**
 * Checks if we are in an invalid setup for the simulation
 */
int	check_for_negative(t_args *args, int argc)
{
	int	res;

	res = 0;
	args->time_to_think = (args->time_to_die
			- args->time_to_eat - args->time_to_sleep) / 2;
	if (args->number_of_philo < 2)
		res = 1;
	if (args->time_to_die < 0)
		res = 1;
	if (args->time_to_eat < 0)
		res = 1;
	if (args->time_to_sleep < 0)
		res = 1;
	if (argc == 6 && args->number_of_times_eat < 0)
		res = 1;
	if (args->time_to_eat + args->time_to_sleep > args->time_to_die)
		res = 1;
	if (res == 1)
		return (printf("unfortunately arguments "),
			printf("provided are not suited for simulation\n"));
	return (0);
}

int	parse_args(int argc, char **argv, t_args *args)
{
	if (argc < 5 || argc > 6)
		return (printf("It seems like the number of argument is incorrect\n"));
	if (ft_is_intnum(argv[1]) == 1)
		args->number_of_philo = ft_atoi(argv[1]);
	else
		return (printf("number of philosopher expect a valid integer\n"));
	if (ft_is_intnum(argv[2]) == 1)
		args->time_to_die = ft_atoi(argv[2]);
	else
		return (printf("time to die expect a valid integer\n"));
	if (ft_is_intnum(argv[3]) == 1)
		args->time_to_eat = ft_atoi(argv[3]);
	else
		return (printf("time to eat expect a valid integer\n"));
	if (ft_is_intnum(argv[4]) == 1)
		args->time_to_sleep = ft_atoi(argv[4]);
	else
		return (printf("time to sleep expect a valid integer\n"));
	if (argc == 6 && ft_is_intnum(argv[5]) == 1)
		args->number_of_times_eat = ft_atoi(argv[5]);
	if (argc == 5)
		args->number_of_times_eat = -1;
	return (check_for_negative(args, argc));
}
