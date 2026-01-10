/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jukerste <jukerste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 16:52:32 by jukerste          #+#    #+#             */
/*   Updated: 2026/01/06 17:22:29 by jukerste         ###   ########.fr       */
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
