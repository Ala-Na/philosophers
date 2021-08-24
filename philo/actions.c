/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/07 17:27:16 by anadege           #+#    #+#             */
/*   Updated: 2021/08/24 20:57:04 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	take_right_fork(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->args->forks[philo->right_fork]))
		return (-1);
	philo->held_forks += 1;
	if (print_action(timestamp(), philo, "has taken a fork") == -1)
		return (-1);
	return (0);
}

int	take_left_fork(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->args->forks[philo->left_fork]))
		return (-1);
	philo->held_forks += 1;
	if (print_action(timestamp(), philo, "has taken a fork") == -1)
		return (-1);
	return (0);
}

int	eat(t_philo *philo)
{
	modify_philo_int_info(philo, &philo->is_eating, 1, 1);
	if (print_action(philo->last_meal, philo, "is eating") == -1)
		return (-1);
	modify_philo_int_info(philo, &philo->meals, -1, 0);
	if (watched_time_pass((unsigned long)philo->args->time_eat,
			philo->last_meal, philo->args))
		return (-1);
	return (0);
}

int	nap(t_philo *philo)
{
	unsigned long	start_nap;

	start_nap = timestamp();
	if (print_action(start_nap, philo, "is sleeping") == -1)
		return (-1);
	pthread_mutex_unlock(&philo->args->forks[philo->right_fork]);
	pthread_mutex_unlock(&philo->args->forks[philo->left_fork]);
	philo->held_forks = 0;
	if (watched_time_pass((unsigned long)philo->args->time_sleep, start_nap,
			philo->args))
		return (-1);
	return (0);
}

int	think(t_philo *philo)
{
	print_action(timestamp(), philo, "is thinking");
	if (philo->args->nbr_philo % 2 == 1)
		usleep((philo->args->time_die / 5));
	return (0);
}
