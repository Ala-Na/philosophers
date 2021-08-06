/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 14:31:59 by anadege           #+#    #+#             */
/*   Updated: 2021/08/06 14:37:56 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

unsigned long	g_launch = -1;

unsigned long	timestamp(void)
{
	struct timeval	time;
	unsigned long	timestamp;

	gettimeofday(&time, NULL);
	if (g_launch == -1)
	{
		g_launch = 1000000 * time.tv_sec + time.tv_usec;
		return (0);
	}
	timestamp = 1000000 * time.tv_sec + time.tv_usec - g_launch;
	return (timestamp);
}
