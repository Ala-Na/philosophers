/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 15:45:17 by anadege           #+#    #+#             */
/*   Updated: 2021/08/12 15:06:37 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_args_mutex(t_arguments *args)
{
	int	i;

	i = 0;
	args->forks = malloc(sizeof(*args->forks) * args->nbr_philo);
	if (!args->forks)
		return (-1);
	while (i < args->nbr_philo)
	{
		pthread_mutex_init(&args->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&args->print_status, NULL);
	pthread_mutex_init(&args->protect_end, NULL);
	return (0);
}

static int	return_value(long int res, int *sign, int cursor)
{
	if (cursor > 10 || ((res < 0 || res > INT_MAX) && *sign > 0))
	{
		*sign = -1;
		return (-1);
	}
	else if ((res < 0 || res * *sign < INT_MIN) && *sign < 0)
	{
		*sign = -1;
		return (0);
	}
	res *= *sign;
	return ((int)res);
}

int	ft_atoi_like(const char *nptr, int *sign)
{
	unsigned int	nbr;
	long int		res;
	int				i;
	int				start;

	i = 0;
	nbr = 0;
	res = 0;
	*sign = 1;
	while (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			*sign = -1;
		i++;
	}
	start = i;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		nbr = nptr[i++] - '0';
		res = res * 10 + nbr;
	}
	return ((int)return_value(res, sign, i - start));
}

int	get_args(char **arr_str, t_arguments *args, int nbr, int *check_nbr)
{
	int	arr_i;
	int	str_i;

	arr_i = -1;
	while (++arr_i < nbr)
	{
		str_i = 0;
		while (arr_str[arr_i][str_i])
			if (!ft_isdigit(arr_str[arr_i][str_i++]))
				return (-1);
		if (arr_i == 0)
			args->nbr_philo = ft_atoi_like(arr_str[arr_i], check_nbr);
		else if (arr_i == 1)
			args->time_die = ft_atoi_like(arr_str[arr_i], check_nbr);
		else if (arr_i == 2)
			args->time_eat = ft_atoi_like(arr_str[arr_i], check_nbr);
		else if (arr_i == 3)
			args->time_sleep = ft_atoi_like(arr_str[arr_i], check_nbr);
		else if (arr_i == 4)
			args->nbr_meals = ft_atoi_like(arr_str[arr_i], check_nbr);
	}
	if (nbr <= 4)
		args->nbr_meals = -1;
	args->end = 0;
	return (0);
}

int	check_and_extract_args(int argc, char **argv, t_arguments *args)
{
	int	check_nbr;

	check_nbr = 0;
	if (get_args(argv + 1, args, argc - 1, &check_nbr) == -1
		|| check_nbr == -1 || init_args_mutex(args) == -1)
	{
		if (args)
			free(args);
		return (-1);
	}
	return (0);
}
