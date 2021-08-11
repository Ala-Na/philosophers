/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scripts.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/07 17:27:16 by anadege           #+#    #+#             */
/*   Updated: 2021/08/11 18:19:35 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	script_for_unique_philo(t_philo *philo, int (*fork_one)(t_philo*))
{
	while (!philo->args->end)
	{
		fork_one(philo);
		return ;
	}
}

void	script_for_philo(t_philo *philo, int (*fork_one)(t_philo*),
		int (*fork_two)(t_philo*))
{
	int	eat_res;

	eat_res = 0;
	while (!philo->args->end)
	{
		if ((!philo->args->end && fork_one(philo) == -1)
			|| (!philo->args->end && fork_two(philo) == -1))
			return ;
		if (!philo->args->end)
			eat_res = eat(philo);
		pthread_mutex_lock(&philo->access_info);
		philo->is_eating = 0;
		pthread_mutex_unlock(&philo->access_info);
		if (eat_res != 0)
			return ;
		if ((!philo->args->end && nap(philo) == -1)
			|| (!philo->args->end && think(philo) == -1))
			return ;
	}
	pthread_mutex_unlock(&philo->args->forks[philo->right_fork]);
	pthread_mutex_unlock(&philo->args->forks[philo->left_fork]);
	return ;
}
