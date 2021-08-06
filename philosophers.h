/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 15:32:54 by anadege           #+#    #+#             */
/*   Updated: 2021/08/06 15:47:15 by anadege          ###   ########.fr       */
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
** Global variable which will equal 1 if one of the ending condition is met.
** (One of the philosophers died or they all had the expected number of meals).
*/
extern int	g_end;

/*
** Global variable to stock timestamp in milliseconds when the programm is launching.
*/
extern unsigned long	g_launch;

/*
** Enum to simplify identification of philosophers' state.
*/
typedef enum	e_state
{
	EAT,
	SLEEP,
	THINK,
	MUERTE
}	t_state;

/*
** Structure to stock arguments of philo programm.
*/
typedef struct	s_arguments
{
	int		nbr_philo;
	int		time_die;
	int		time_eat;
	int		time_sleep;
	int		nbr_meals;
}	t_arguments;

/*
** Structure representing each philosophers.
*/
typedef struct	s_philo
{
	int				philo_id;
	pthread_t		thread;
	t_state			state;
	int				priority;
	unsigned long	last_meal;
	int				nbr_meals;
	t_arguments		*args;
	struct s_philo	*others;
}	t_philo;

/*
** Function to get timestamp since programm launch.
*/
unsigned long	timestamp(void);

/*
** Parsing functions to extract arguments.
*/
int	check_and_extract_args(int agrc, char **argv, t_arguments *args);
int	get_args(char **arr_str, t_arguments *args, int nbr, int *check_nbr);
int	ft_isdigit(int c);
int ft_atoi_like(const char *nptr, int *check_nbr);

/*
**
*/
t_philo	*init_philo(t_arguments *args);
int		init_threads(t_philo *philo, t_arguments *args);
void	*philo_launch(void *received);

#endif
