/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaigne <emaigne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 12:47:36 by emaigne           #+#    #+#             */
/*   Updated: 2026/03/09 14:43:18 by emaigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# ifndef IS_DEBUG
#  define IS_DEBUG 0
# endif

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>

typedef struct s_args
{
	int	number_of_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_of_times_eat;
	int	time_to_think;
}	t_args;

//		---utils---			//
int		ft_atoi(const char *str);
int		ft_is_intnum(char *str);

//		---parsing---		//
int		parse_args(int argc, char **argv, t_args *args);

//		---debug---			//
void	print_params(t_args *args);

#endif