/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scripts.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/07 17:27:16 by anadege           #+#    #+#             */
/*   Updated: 2021/08/24 20:02:07 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	script_for_unique_philo(t_philo *philo, int (*fork_one)(t_philo*))
{
	while (!check_end(philo->args, 0))
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
	while (!check_end(philo->args, 0))
	{
		if (fork_one(philo) == -1
			|| (printf("start check for %i\n", philo->id)
			&& !check_end(philo->args, 0)
			&& printf("end check for %i\n", philo->id) && fork_two(philo) == -1))
			return ;
		eat_res = eat(philo);
		pthread_mutex_lock(&philo->access_info);
		philo->is_eating = 0;
		pthread_mutex_unlock(&philo->access_info);
		if (eat_res != 0)
			return ;
		if ((!check_end(philo->args, 0) && nap(philo) == -1)
			|| (!check_end(philo->args, 0) && think(philo) == -1))
		{
			return ;
		}
	}
	return ;
}
