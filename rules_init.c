/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jukerste <jukerste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 13:26:37 by jukerste          #+#    #+#             */
/*   Updated: 2025/12/23 13:26:59 by jukerste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


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
