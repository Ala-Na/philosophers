/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 14:31:59 by anadege           #+#    #+#             */
/*   Updated: 2021/08/10 21:00:29 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

unsigned long	g_launch = -1;

unsigned long	timestamp(void)
{
	struct timeval	time;
	unsigned long	timestamp;

	gettimeofday(&time, NULL);
	if (g_launch == -1)
	{
		g_launch = 1000 * time.tv_sec + time.tv_usec / 1000;
		return (0);
	}
	timestamp = 1000 * time.tv_sec + time.tv_usec / 1000 - g_launch;
	return (timestamp);
}

int	watch_time(unsigned long action_time, unsigned long start,
		t_arguments *args)
{
	while (!args->end)
	{
		if (timestamp() >= action_time + start)
			break ;
	}
	return (0);
}

int	print_action(unsigned long time, t_philo *philo, char *str)
{
	if (!philo->args->end)
	{
		if (pthread_mutex_lock(&philo->args->print_status))
			return (-1);
		if (!philo->args->end)
		{
			printf("%li ", time);
			printf("%i ", philo->id);
			printf("%s\n", str);
		}
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
