/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 15:32:34 by anadege           #+#    #+#             */
/*   Updated: 2021/08/25 14:39:59 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	error_message(int error)
{
	if (error == -2)
	{
		printf("Error in  arguments received.\n\nphilo need 4 or 5 arguments");
		printf(" which should be positive integers superior to 0 for");
		printf(" philosophers or 60 milliseconds for times):\n");
		printf("[number_of_philosophers]");
		printf("\n[time_to_die]\n[time_to_eat]\n[time_to_sleep]\n");
		printf("[number_of_times_each_philosopher_must_eat] (additionnal)\n\n");
	}
	else
		printf("!!! Alert : philo crashed !!!\n");
	return (-1);
}

int	exit_management(int exit, t_arguments *args, void *forks, t_philo *philo)
{
	int	i;

	i = -1;
	if (philo)
	{
		while (++i < args->nbr_philo)
			pthread_mutex_destroy(&philo[i].access_info);
		free(philo);
	}
	i = -1;
	if (args)
	{
		pthread_mutex_destroy(&args->print_status);
		pthread_mutex_destroy(&args->protect_end);
		if (forks)
		{
			while (++i < args->nbr_philo)
				pthread_mutex_destroy(&args->forks[i]);
			free(args->forks);
		}
		free(args);
	}
	if (exit < 0)
		return (error_message(exit));
	return (0);
}

int	main(int argc, char **argv)
{
	t_arguments	*args;
	t_philo		*philo;
	void		*forks;

	args = NULL;
	forks = NULL;
	philo = NULL;
	args = malloc(sizeof(*args));
	if (!args)
		return (-1);
	if (argc < 5 || argc > 6 || check_and_extract_args(argc, argv, args, &forks) == -1)
		return (exit_management(-2, NULL, forks, philo));
	philo = init_philo(args);
	if (!philo || init_threads(philo, args) == -1)
		return (exit_management(-1, args, forks, philo));
	return (exit_management(0, args, forks, philo));
}
