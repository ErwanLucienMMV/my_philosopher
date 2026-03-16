/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaigne <emaigne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 14:15:13 by emaigne           #+#    #+#             */
/*   Updated: 2026/03/16 17:32:43 by emaigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	main(int argc, char **argv)
{
	t_args	args;
	t_table	table;

	if (parse_args(argc, argv, &args))
		return (1);
	table.args = args;
	if (!init_mutexes(&table))
	{
		if (initialize_philo(&table))
			return (cleanup_forks(&table), 1);
		table.start_time = get_time();
		if (!start_simulation(&table))
		{
			wait_threads(&table);
		}
	}
	return (cleanup(&table), 0);
}
