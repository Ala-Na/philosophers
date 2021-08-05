/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 15:32:34 by anadege           #+#    #+#             */
/*   Updated: 2021/08/05 21:11:11 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_arguments	*args;

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
	printf("philo : %i, die : %i, eat : %i, sleep : %i, meals : %i\n", args->nbr_philo, args->time_die, args->time_eat, args->time_sleep, args->nbr_meals);
	free(args);
	return (0);
}
