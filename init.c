/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jul <jul@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 16:18:45 by jul               #+#    #+#             */
/*   Updated: 2026/01/05 02:53:30 by jul              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_mutexes(t_rules *rules)
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
	return (0);
}

static int	create_philos(t_rules *rules)
{
	int	i;

	rules->philos = malloc(sizeof(t_philo) * rules->total_philos);
	if (!rules->philos)
		return (1);
	i = 0;
	while (i < rules->total_philos)
	{
		rules->philos[i].id = i + 1;
		rules->philos[i].meals_eaten = 0;
		rules->philos[i].last_meal_time = get_time_in_ms();
		rules->philos[i].rules = rules;
		rules->philos[i].left_fork = &rules->forks[i];
		rules->philos[i].right_fork = &rules->forks[(i + 1) % rules->total_philos];
		if (pthread_mutex_init(&rules->philos[i].meal_mutex, NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	philosophers_and_forks(t_rules *rules)
{
	rules->philo_died = 0;
	if (init_mutexes(rules) != 0)
		return (1);
	if (create_philos(rules) != 0)
		return (1);
	return (0);
}
