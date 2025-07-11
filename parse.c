/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jul <jul@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 16:20:04 by jukerste          #+#    #+#             */
/*   Updated: 2025/07/11 17:43:57 by jul              ###   ########.fr       */
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

int	parse_args(int argc, char **argv, t_rules *rules)
{
	if (argc != 5 && argc != 6)
		return (1);
	if (!is_only_digits(argv[1]) || !is_only_digits(argv[2])
	|| !is_only_digits(argv[3]) || !is_only_digits(argv[4]) || 
	(argc == 6 && !is_only_digits(argv[5])))
		return (1);
	rules->total_philos = ft_atol(argv[1]);
	rules->time_to_die = ft_atol(argv[2]);
	rules->time_to_eat = ft_atol(argv[3]);
	rules->time_to_sleep = ft_atol(argv[4]);
	if (argc == 6)
		rules->must_eat_count = ft_atol(argv[5]);
	else
		rules->must_eat_count = -1;
	if (rules->total_philos <= 0 || rules->time_to_die <= 0 ||
	rules->time_to_eat <= 0 || rules->time_to_sleep <= 0 || (argc == 6 
	&& rules->must_eat_count <= 0))
		return (1);
	return (0);
}
