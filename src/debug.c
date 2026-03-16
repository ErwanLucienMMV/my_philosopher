/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaigne <emaigne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 14:38:20 by emaigne           #+#    #+#             */
/*   Updated: 2026/03/16 17:10:15 by emaigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	print_params(t_args *args)
{
	if (IS_DEBUG)
	{
		printf("current param are:\n");
		printf("Number of philo: %d\n", args->number_of_philo);
		printf("Time to die: %ld\n", args->time_to_die);
		printf("Time to eat: %ld\n", args->time_to_eat);
		printf("Time to sleep: %ld\n", args->time_to_sleep);
		printf("Time to think: %ld\n", args->time_to_think);
		printf("Number of time they must eat (if given): %d\n",
			args->number_of_times_eat);
	}
}
