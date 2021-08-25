/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 15:32:54 by anadege           #+#    #+#             */
/*   Updated: 2021/08/25 13:54:39 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>
# include <limits.h>

/*
** Global variable to stock timestamp in milliseconds when the programm
** is launching.
*/
extern unsigned long	g_launch;

/*
** Structure to stock arguments of philo programm.
*/
typedef struct s_arguments
{
	int				nbr_philo;
	unsigned long	time_die;
	unsigned long	time_eat;
	unsigned long	time_sleep;
	int				nbr_meals;
	pthread_mutex_t	print_status;
	pthread_mutex_t	*forks;
	pthread_mutex_t	protect_end;
	int				end;
}	t_arguments;

/*
** Structure representing each philosophers.
*/
typedef struct s_philo
{
	pthread_mutex_t	access_info;
	int				id;
	pthread_t		thread;
	int				meals;
	unsigned long	last_meal;
	int				is_eating;
	int				right_fork;
	int				left_fork;
	int				held_forks;
	t_arguments		*args;
}	t_philo;

/*
** Function to get timestamp since programm launch.
*/
unsigned long	timestamp(void);
int				watched_time_pass(unsigned long action_time,
					unsigned long start, t_arguments *args);
int				modify_philo_int_info(t_philo *philo, int *info, int new_res,
					int new_time);

int				print_action(unsigned long time, t_philo *philo, char *str);

int				check_and_extract_args(int agrc, char **argv,
					t_arguments *args, void **forks);
int				get_args(char **arr_str, t_arguments *args, int nbr,
					int *check_nbr);
int				ft_isdigit(int c);
int				ft_atoi_like(const char *nptr, int *sign);

t_philo			*init_philo(t_arguments *args);
int				init_threads(t_philo *philo, t_arguments *args);
void			*philo_launch(void *received);

void			script_for_philo(t_philo *philo, int (*fork_one)(t_philo *),
					int (*fork_two)(t_philo*));
void			script_for_unique_philo(t_philo *philo,
					int (*fork_one)(t_philo *));

int				take_right_fork(t_philo *philo);
int				take_left_fork(t_philo *philo);
int				think(t_philo *philo);
int				nap(t_philo *philo);
int				eat(t_philo *philo);

int				check_nbr_of_meals(t_philo *philo, t_arguments *args);
int				check_if_dead(t_philo *philo, t_arguments *args);
int				check_end(t_arguments *args, int change);
int				check_is_eating(t_philo *philo);
int				check_last_meal(t_philo *philo, t_arguments *args,
					unsigned long curr_time);

int				exit_management(int exit, t_arguments *args, void *forks,
					t_philo *philo);
int				error_message(int error);

#endif
