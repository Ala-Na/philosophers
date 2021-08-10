/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 08:57:29 by anadege           #+#    #+#             */
/*   Updated: 2021/08/10 20:38:22 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_nbr_of_meals(t_philo *philo, t_arguments *args)
{
	int	nbr_meals;
	int	i;

	nbr_meals = args->nbr_meals;
	i = 0;
	while (nbr_meals != -1 && i < args->nbr_philo
		&& philo[i].meals >= nbr_meals)
		i++;
	if (nbr_meals != -1 && i == args->nbr_philo)
	{
		philo->args->end = 1;
		return (1);
	}
	return (0);
}

int	check_if_dead(t_philo *philo, t_arguments *args)
{
	int				i;
	unsigned long	curr_time;

	i = 0;
	curr_time = timestamp();
	while (i < args->nbr_philo)
	{
		if ((curr_time - philo[i].last_meal) > args->time_die
			&& !pthread_mutex_lock(&philo[i].is_eating))
		{
			args->end += 1;
			pthread_mutex_lock(&args->print_status);
			if (args->end == 1)
				printf("%li %i is dead\n", curr_time, i + 1);
			pthread_mutex_unlock(&args->print_status);
			pthread_mutex_unlock(&philo[i].is_eating);
			return (1);
		}
		pthread_mutex_unlock(&philo[i].is_eating);
		i++;
	}
	return (0);
}
