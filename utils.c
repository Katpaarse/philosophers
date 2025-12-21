/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jul <jul@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 16:52:32 by jukerste          #+#    #+#             */
/*   Updated: 2025/12/21 17:01:03 by jul              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_only_digits(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

long	ft_atol_converter(char const *str, int i, int sign)
{
	long	num;

	num = 0;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (num > (INT_MAX - (str[i] - '0')) / 10)
		{
			if (sign == 1)
				return (INT_MAX);
			else
				return (INT_MIN);
		}
		num = num * 10 + (str[i] - '0');
		i++;
	}
	return (num * sign);
}

long	ft_atol(char const *str)
{
	int		i;
	int		sign;

	i = 0;
	sign = 1;
	return (ft_atol_converter(str, i, sign));
}

void	init_rules(t_rules *rules)
{
	rules->total_philos = 0;
	rules->time_to_die = 0;
	rules->time_to_eat = 0;
	rules->time_to_sleep = 0;
	rules->must_eat_count = -1;
	rules->philo_died = 0;
	rules->start_time = 0;
	rules->forks = NULL;
	rules->philos = NULL;
}
