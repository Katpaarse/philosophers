/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jukerste <jukerste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 16:25:07 by jukerste          #+#    #+#             */
/*   Updated: 2026/01/06 15:56:46 by jukerste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_for_death(t_philo *philo)
{
	long	current_time;

	current_time = get_time_in_ms();
	pthread_mutex_lock(&philo->meal_mutex);
	if (current_time - philo->last_meal_time >= philo->rules->time_to_die)
	{
		pthread_mutex_lock(&philo->rules->death_mutex);
		philo->rules->philo_died = 1;
		pthread_mutex_unlock(&philo->rules->death_mutex);
		pthread_mutex_lock(&philo->rules->print_mutex);
		printf("%ld %d died\n", current_time - philo->rules->start_time,
			philo->id);
		pthread_mutex_unlock(&philo->rules->print_mutex);
		pthread_mutex_unlock(&philo->meal_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->meal_mutex);
	return (0);
}

static int	check_all_ate(t_rules *rules)
{
	int	i;
	int	all_ate;

	i = 0;
	all_ate = 1;
	if (rules->must_eat_count == -1)
		return (0);
	while (i < rules->total_philos)
	{
		pthread_mutex_lock(&rules->philos[i].meal_mutex);
		if (rules->philos[i].meals_eaten < rules->must_eat_count)
			all_ate = 0;
		pthread_mutex_unlock(&rules->philos[i].meal_mutex);
		i++;
	}
	if (all_ate)
	{
		pthread_mutex_lock(&rules->death_mutex);
		rules->philo_died = 1;
		pthread_mutex_unlock(&rules->death_mutex);
		return (1);
	}
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_rules	*rules;
	int		i;

	rules = (t_rules *)arg;
	while (1)
	{
		i = 0;
		while (i < rules->total_philos)
		{
			if (check_for_death(&rules->philos[i]))
				return (NULL);
			i++;
		}
		if (check_all_ate(rules))
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}
