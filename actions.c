/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/07 17:27:16 by anadege           #+#    #+#             */
/*   Updated: 2021/08/07 17:53:34 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	take_right_fork(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->right_fork) != 0
			|| pthread_mutex_lock(&philo->args->print_status) != 0)
		return (-1);
	printf("%5li %i has taken a fork\n", timestamp(), philo->philo_id);
	if (pthread_mutex_unlock(&philo->args->print_status) != 0)
		return (-1);
	return (0);
}

int	take_left_fork(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->left_fork) != 0
			|| pthread_mutex_lock(&philo->args->print_status) != 0)
		return (-1);
	printf("%5li %i has taken a fork\n", timestamp(), philo->philo_id);
	if (pthread_mutex_unlock(&philo->args->print_status) != 0)
		return (-1);
	return (0);
}

int	eat(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->args->print_status) != 0)
		return (-1);
	printf("%5li %i is eating\n", timestamp(), philo->philo_id);
	if (pthread_mutex_unlock(&philo->args->print_status) != 0
			|| usleep(philo->args->time_eat * 1000) != 0)
		return (-1);
	return (0);
}

int	nap(t_philo *philo)
{
	if (pthread_mutex_unlock(&philo->left_fork) != 0
			|| pthread_mutex_unlock(&philo->right_fork) != 0
			|| pthread_mutex_lock(&philo->args->print_status) != 0)
		return (-1);
	printf("%5li %i is sleeping\n", timestamp(), philo->philo_id);
	if (pthread_mutex_unlock(&philo->args->print_status) != 0
			|| usleep(philo->args->time_sleep * 1000) != 0)
		return (-1);
	return (0);
}

int think(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->args->print_status) != 0)
		return (-1);
	printf("%5li %i is thinking\n", timestamp(), philo->philo_id);
	if (pthread_mutex_unlock(&philo->args->print_status) != 0)
		return (-1);
	return (0);

}
