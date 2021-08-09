/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scripts.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/07 17:27:16 by anadege           #+#    #+#             */
/*   Updated: 2021/08/09 20:24:32 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	script_for_philo(t_philo *philo, int (*fork_one)(t_philo*),
		int (*fork_two)(t_philo*))
{
	int	eat_res;

	eat_res = 0;
	while (!philo->args->end)
	{
		if ((!philo->args->end && fork_one(philo) == -1)
			||(!philo->args->end && fork_two(philo) == -1))
			return (-1);
		if (!philo->args->end)
			eat_res = eat(philo);
		if (eat_res != 0)
			return (eat_res);
		if((!philo->args->end && nap(philo) == -1)
			|| (!philo->args->end && think(philo) == -1))
			return (-1);
	}
	pthread_mutex_unlock(&philo->args->forks[philo->right_fork]);
	pthread_mutex_unlock(&philo->args->forks[philo->left_fork]);
	return (0);
}
