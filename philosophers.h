/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 15:32:54 by anadege           #+#    #+#             */
/*   Updated: 2021/08/05 21:09:26 by anadege          ###   ########.fr       */
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
** Structure to stock arguments of philo programm.
*/
typedef struct	s_arguments
{
	int	nbr_philo;
	int	time_die;
	int	time_eat;
	int	time_sleep;
	int	nbr_meals;
}	t_arguments;

/*
** Parsing functions to extract arguments.
*/
int	check_and_extract_args(int agrc, char **argv, t_arguments *args);
int	get_args(char **arr_str, t_arguments *args, int nbr, int *check_nbr);
int	ft_isdigit(int c);
int ft_atoi_like(const char *nptr, int *check_nbr);

#endif
