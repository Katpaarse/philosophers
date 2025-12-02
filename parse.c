/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jukerste <jukerste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 16:20:04 by jukerste          #+#    #+#             */
/*   Updated: 2025/12/02 11:57:56 by jukerste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parse_args(int argc, char **argv, t_rules *rules)
{
	if (argc != 5 && argc != 6)
		return (1);
	if (!is_only_digits(argv[1]) || !is_only_digits(argv[2]) || !is_only_digits(argv[3]) || !is_only_digits(argv[4]) || (argc == 6 && !is_only_digits(argv[5])))
		return (1);
	rules->total_philos = ft_atol(argv[1]);
	rules->time_to_die = ft_atol(argv[2]);
	rules->time_to_eat = ft_atol(argv[3]);
	rules->time_to_sleep = ft_atol(argv[4]);
	if (argc == 6)
		rules->must_eat_count = ft_atol(argv[5]);
	else
		rules->must_eat_count = -1;
	if (rules->total_philos <= 0 || rules->time_to_die <= 0 || rules->time_to_eat <= 0 || rules->time_to_sleep <= 0 || (argc == 6 && rules->must_eat_count <= 0))
		return (1);
	return (0);
}
