/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 14:41:48 by anadege           #+#    #+#             */
/*   Updated: 2021/08/06 16:01:12 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*philo_launch(void *received)
{
	t_philo	*philo;
	philo = (t_philo *)received;
	printf("philo id is %i with state %i and priority %i.\n", philo->philo_id, philo->state, philo->priority);
	int i = 0;
	printf("Others : ");
	while (i < philo->args->nbr_philo)
	{
		if (i + 1 != philo->philo_id)
			printf("philo n°%i, ", philo->others[i].philo_id);
		i++;
	}
	printf("\n");
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
	usleep(10000000);
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
		philo[i].priority = 0;
		philo[i].last_meal = 0;
		philo[i].nbr_meals = 0;
		philo[i].args = args;
		philo[i].others = philo;
		i++;
	}
	return (philo);
}
