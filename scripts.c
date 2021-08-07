/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scripts.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/07 17:27:16 by anadege           #+#    #+#             */
/*   Updated: 2021/08/07 17:53:50 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	script_for_odd(t_philo *philo)
{
	if (take_left_fork(philo) == -1 || take_right_fork(philo) == -1
			|| eat(philo) == -1 || nap(philo) == -1
			|| think(philo) == -1)
		return (-1);
	return (0);
}

int	script_for_even(t_philo *philo)
{
	if (take_right_fork(philo) == -1 || take_left_fork(philo) == -1
			|| eat(philo) == -1 || nap(philo) == -1
			|| think(philo) == -1)
		return (-1);
	return (0);
}
