/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jul <jul@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 16:18:45 by jul               #+#    #+#             */
/*   Updated: 2025/12/21 14:23:18 by jul              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philosophers_and_forks(t_rules *rules)
{
	int	i;

	if (pthread_mutex_init(&rules->print_mutex, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&rules->death_mutex, NULL) != 0)
		return (1);
	rules->philo_died = 0;
	rules->forks = malloc(sizeof(pthread_mutex_t) * rules->total_philos);
	if (!rules->forks)
		return (1);
	i = 0;
	while (i < rules->total_philos)
	{
		if (pthread_mutex_init(&rules->forks[i], NULL) != 0)
			return (1);
		i++;
	}
	rules->philos = malloc(sizeof(t_philo) * rules->total_philos);
	if (!rules->philos)
		return (1);
	i = 0;
	while (i < rules->total_philos)
	{
		rules->philos[i].id = i + 1;
		rules->philos[i].meals_eaten = 0;
		rules->philos[i].last_meal_time = rules->start_time;
		rules->philos[i].rules = rules;
		rules->philos[i].left_fork = &rules->forks[i];
		rules->philos[i].right_fork = &rules->forks[(i + 1) % rules->total_philos];
		i++;
	}
	return (0);
}
