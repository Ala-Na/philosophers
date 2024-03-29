/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 08:57:29 by anadege           #+#    #+#             */
/*   Updated: 2021/08/25 10:35:39 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_nbr_of_meals(t_philo *philo, t_arguments *args)
{
	int	nbr_meals;
	int	i;

	nbr_meals = args->nbr_meals;
	i = 0;
	while (nbr_meals != -1 && i < args->nbr_philo)
	{
		pthread_mutex_lock(&philo->access_info);
		if (philo[i].meals >= nbr_meals)
			i++;
		else
		{
			pthread_mutex_unlock(&philo->access_info);
			break ;
		}
		pthread_mutex_unlock(&philo->access_info);
	}
	if (nbr_meals != -1 && i == args->nbr_philo)
	{
		pthread_mutex_lock(&args->protect_end);
		philo->args->end = 1;
		pthread_mutex_unlock(&args->protect_end);
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
		if (!pthread_mutex_lock(&args->print_status)
			&& check_is_eating(&philo[i]) == 0
			&& check_last_meal(&philo[i], args, curr_time))
		{
			if (check_end(args, 1) == 1)
				printf("%li %i died\n", curr_time, i + 1);
			pthread_mutex_unlock(&args->print_status);
			return (1);
		}
		pthread_mutex_unlock(&args->print_status);
		i++;
	}
	return (0);
}

int	check_last_meal(t_philo *philo, t_arguments *args, unsigned long curr_time)
{
	int	res;

	pthread_mutex_lock(&philo->access_info);
	if (curr_time - philo->last_meal >= args->time_die)
		res = 1;
	else
		res = 0;
	pthread_mutex_unlock(&philo->access_info);
	return (res);
}

int	check_end(t_arguments *args, int change)
{
	int	res;

	pthread_mutex_lock(&args->protect_end);
	if (change == 1)
		args->end += 1;
	res = args->end;
	pthread_mutex_unlock(&args->protect_end);
	return (res);
}

int	check_is_eating(t_philo *philo)
{
	int	res;

	pthread_mutex_lock(&philo->access_info);
	res = philo->is_eating;
	pthread_mutex_unlock(&philo->access_info);
	return (res);
}
