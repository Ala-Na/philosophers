/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 14:31:59 by anadege           #+#    #+#             */
/*   Updated: 2021/08/12 17:52:56 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

unsigned long	g_launch = -1;

unsigned long	timestamp(void)
{
	struct timeval	time;
	unsigned long	timestamp;

	gettimeofday(&time, NULL);
	if ((int)g_launch == -1)
	{
		g_launch = 1000 * time.tv_sec + time.tv_usec / 1000;
		return (0);
	}
	timestamp = 1000 * time.tv_sec + time.tv_usec / 1000 - g_launch;
	return (timestamp);
}

int	watched_time_pass(unsigned long action_time, unsigned long start,
		t_arguments *args)
{
	while (!check_end(args, 0))
	{
		if (timestamp() >= action_time + start)
			break ;
	}
	return (0);
}

int	print_action(unsigned long time, t_philo *philo, char *str)
{
	if (!check_end(philo->args, 0))
	{
		if (pthread_mutex_lock(&philo->args->print_status))
			return (-1);
		if (!pthread_mutex_lock(&philo->access_info) && !philo->args->end)
		{
			printf("%li ", time);
			printf("%i ", philo->id);
			printf("%s\n", str);
		}
		pthread_mutex_unlock(&philo->access_info);
		if (pthread_mutex_unlock(&philo->args->print_status))
			return (-1);
	}
	return (0);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (2048);
	return (0);
}

int	modify_philo_int_info(t_philo *philo, int *info, int new_res, int new_time)
{
	if (pthread_mutex_lock(&philo->access_info))
		return (-1);
	if (new_res == -1)
		*info += 1;
	else
		*info = new_res;
	if (new_time == 1)
		philo->last_meal = timestamp();
	pthread_mutex_unlock(&philo->access_info);
	return (1);
}
