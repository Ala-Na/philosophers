/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 20:40:20 by anadege           #+#    #+#             */
/*   Updated: 2021/08/11 12:01:22 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*philo_launch(void *received)
{
	t_philo	*philo;

	philo = (t_philo *)received;
	if (philo->args->nbr_philo == 1)
		script_for_unique_philo(philo, &take_left_fork);
	else if (philo->id % 2 == 1)
		script_for_philo(philo, &take_left_fork, &take_right_fork);
	else if (philo->id % 2 == 0 && !philo->args->end)
	{
		usleep(10);
		script_for_philo(philo, &take_right_fork, &take_left_fork);
	}
	return (NULL);
}

int	init_threads(t_philo *philo, t_arguments *args)
{
	int	i;

	i = -1;
	while (++i < args->nbr_philo)
	{
		if (pthread_create(&philo[i].thread, NULL, &philo_launch,
				(void *)&philo[i]))
			return (-1);
	}
	while (1)
	{
		usleep(1000);
		if (check_nbr_of_meals(philo, args) == 1
			|| check_if_dead(philo, args) == 1)
		{
			i = -1;
			while (++i < args->nbr_philo)
				pthread_join(philo[i].thread, NULL);
			return (0);
		}
	}
	return (0);
}

t_philo	*init_philo(t_arguments *args)
{
	int		i;
	t_philo	*philo;

	i = 0;
	philo = malloc(sizeof(*philo) * args->nbr_philo);
	if (!philo)
		return (NULL);
	while (i < args->nbr_philo)
	{
		philo[i].id = i + 1;
		philo[i].meals = 0;
		philo[i].args = args;
		philo[i].last_meal = 0;
		pthread_mutex_init(&philo[i].is_eating, NULL);
		philo[i].right_fork = philo[i].id;
		if (philo[i].id == args->nbr_philo)
			philo[i].right_fork = 0;
		philo[i].left_fork = philo[i].id - 1;
		i++;
	}
	return (philo);
}
