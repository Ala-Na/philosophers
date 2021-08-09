/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 14:41:48 by anadege           #+#    #+#             */
/*   Updated: 2021/08/09 16:47:20 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*philo_launch(void *received)
{
	t_philo	*philo;
	int		res;

	philo = (t_philo *)received;
	if (philo->id % 2 == 1)
		script_for_philo(philo, &take_left_fork, &take_right_fork);
	if (philo->id % 2 == 0 && !philo->args->end)
	{
		usleep(50);
		script_for_philo(philo, &take_right_fork, &take_left_fork);
	}
	return (NULL);
}

int	init_threads(t_philo *philo, t_arguments *args)
{
	int	i;

	i = 0;
	while (i < args->nbr_philo)
	{
		if (pthread_create(&philo[i].thread, NULL, &philo_launch, (void *)&philo[i]))
			return (-1);
		i++;
	}
	while (1)
	{
		usleep(10000);
		if (check_nbr_of_meals(philo, args) == 1
			|| check_if_dead(philo, args) == 1)
		{
			i = 0;
			while (i < args->nbr_philo)
			{
				pthread_join(philo[i].thread, NULL);
				i++;
			}
			return (0);
		}
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
		philo[i].id = i + 1;
		philo[i].meals = 0;
		philo[i].args = args;
		philo[i].last_meal = 0;
		philo[i].right_fork = philo[i].id;
		if (philo[i].id == args->nbr_philo)
			philo[i].right_fork = 0;
		philo[i].left_fork = philo[i].id - 1;
		i++;
	}
	return (philo);
}
