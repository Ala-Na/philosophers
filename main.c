/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 15:32:34 by anadege           #+#    #+#             */
/*   Updated: 2021/08/06 22:48:15 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_arguments	*args;
	t_philo		*philo;

	args = malloc(sizeof(*args));
	if (!args)
		return (-1);
	if (argc < 5 || argc > 6)
	{
		free(args);
		printf("%i arguments received.\nPhilosophers should receive 4 arguments :\nnumber_of_philosophers time_to_die time_to_eat time_to_sleep.\nAdditionnal argument number_of_times_each_philosopher_must_eat can be added.\n", argc - 1);
		return (-1);
	}
	if (check_and_extract_args(argc, argv, args) == -1)
	{
		printf("Error in arguments received.\nThey must be positive integers.\n");
		return (-1);
	}
	philo = init_philo(args);
	if (!philo)
	{
		free(args->forks);
		free(args);
		return (-1);
	}
	if(init_threads(philo, args) == -1)
	{
		free(args->forks);
		free(args);
		free(philo);
		return (-1);
	}
	free(args->forks);
	free(args);
	free(philo);
	return (0);
}
