/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 14:31:59 by anadege           #+#    #+#             */
/*   Updated: 2021/08/09 20:39:33 by anadege          ###   ########.fr       */
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

int	watch_time(unsigned long action_time, t_arguments *args)
{
	int	i;

	i = timestamp();
	while (!args->end)
	{
		if (timestamp() - i >= action_time)
			break;
		if (usleep(1000) != 0)
			return (-1);
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
			printf("%li %i %s\n", time, philo->id, str);
		if (pthread_mutex_unlock(&philo->args->print_status))
			return (-1);
	}
	return (0);
}
