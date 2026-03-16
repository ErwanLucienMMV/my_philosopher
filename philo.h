/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaigne <emaigne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 12:47:36 by emaigne           #+#    #+#             */
/*   Updated: 2026/03/16 17:17:29 by emaigne          ###   ########.fr       */
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
# include <sys/time.h>
# include <unistd.h>

typedef struct s_args
{
	int		number_of_philo;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	int		number_of_times_eat;
	long	time_to_think;
}	t_args;

typedef struct s_table
{
	t_args			args;
	long			start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	stop_mutex;
	int				stop_simulation;
	pthread_t		monitor;
	struct s_philo	*philos;
}	t_table;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	long			last_meal;
	int				meals_eaten;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_table			*table;
}	t_philo;

//		---utils---			//
int		ft_atoi(const char *str);
int		ft_is_intnum(char *str);
long	get_time(void);
long	time_since_start(t_table *table);
long	time_since_last_meal(t_philo *philo);

//		---parsing---		//
int		parse_args(int argc, char **argv, t_args *args);

//		---Init---			//
void	assign_forks(t_table *table, int i);
int		init_mutexes(t_table *table);
int		init_philo(t_table *table, int i);
int		initialize_philo(t_table *table);

//		---Cleanup---		//
void	cleanup_forks(t_table *table);
void	cleanup(t_table *table);

//		---Simulation Helpers---//
int		start_simulation(t_table *table);
void	wait_threads(t_table *table);
int		simulation_stopped(t_table *table);
void	print_status(t_philo *philo, char *msg);
void	smart_sleep(long time, t_table *table);

//		---Simulation---	//
void	*philo_routine(void *arg);
void	*monitor_routine(void *arg);
int		start_simulation(t_table *table);
void	wait_threads(t_table *table);

//		---debug---			//
void	print_params(t_args *args);

#endif