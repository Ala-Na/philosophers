/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 14:41:48 by anadege           #+#    #+#             */
/*   Updated: 2021/08/06 22:46:34 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*philo_launch(void *received)
{
	t_philo	*philo;
	philo = (t_philo *)received;
	printf("philo id is %i with state %i.\n", philo->philo_id, philo->state);
	return ((void *)philo);
}

int	init_threads(t_philo *philo, t_arguments *args)
{
	int	i;

	i = 0;
	while (i < args->nbr_philo)
	{
		if (pthread_create(&philo[i].thread, NULL, &philo_launch, (void *)&philo[i]) != 0)
			return (-1);
		i++;
	}
	i = 0;
	while (i < args->nbr_philo)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
	return (0);
}

/*
** Initialize the function t_philo which contains main informations about
** each philosophers.
** pthread_t is not initialized at this state as the function pthread_create
** will 
*/
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
		philo[i].philo_id = i + 1;
		philo[i].state = THINK;
		if (i + 1 < args->nbr_philo)
			philo[i].left_fork = args->forks[i + 1];
		else
			philo[i].right_fork = args->forks[0];
		philo[i].right_fork = args->forks[i];
		philo[i].meals = 0;
		philo[i].args = args;
		i++;
	}
	return (philo);
}
