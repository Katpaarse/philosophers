/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jul <jul@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 15:00:13 by jukerste          #+#    #+#             */
/*   Updated: 2026/01/05 14:18:33 by jul              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	take_forks(t_philo *philo)
{
	t_rules	*rules;
	
	rules = philo->rules;
	
	if (philo->id % 2 == 0)
	{
		// Even IDs: take right fork first
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken a fork");
		
		// Check death before taking second fork
		pthread_mutex_lock(&rules->death_mutex);
		if (rules->philo_died)
		{
			pthread_mutex_unlock(&rules->death_mutex);
			pthread_mutex_unlock(philo->right_fork);
			return (0);
		}
		pthread_mutex_unlock(&rules->death_mutex);
		
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork");
	}
	else
	{
		// Odd IDs: take left fork first
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork");
		
		// Check death before taking second fork
		pthread_mutex_lock(&rules->death_mutex);
		if (rules->philo_died)
		{
			pthread_mutex_unlock(&rules->death_mutex);
			pthread_mutex_unlock(philo->left_fork);
			return (0);
		}
		pthread_mutex_unlock(&rules->death_mutex);
		
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken a fork");
	}
	return (1);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	t_rules	*rules;
	
	philo = (t_philo *)arg;
	rules = philo->rules;
	
	if (rules->total_philos == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(&rules->death_mutex);
		philo->last_meal_time = get_time_in_ms();
		pthread_mutex_unlock(&rules->death_mutex);
		smart_sleep(rules->time_to_die, rules);
		pthread_mutex_unlock(philo->left_fork);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		usleep(15000);
	while (1)
	{
		// Check death at start of each cycle
		pthread_mutex_lock(&rules->death_mutex);
		if (rules->philo_died)
		{
			pthread_mutex_unlock(&rules->death_mutex);
			break;
		}
		pthread_mutex_unlock(&rules->death_mutex);
		
		print_status(philo, "is thinking");
		
		// Take forks with death checks
		if (!take_forks(philo))
			break;
		
		// Eat - update last meal time atomically
		pthread_mutex_lock(&rules->death_mutex);
		philo->last_meal_time = get_time_in_ms();
		philo->meals_eaten++;
		pthread_mutex_unlock(&rules->death_mutex);
		
		print_status(philo, "is eating");
		smart_sleep(rules->time_to_eat, rules);
		
		// Release forks
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		
		// Check if philosopher has eaten enough
		pthread_mutex_lock(&rules->death_mutex);
		if (rules->must_eat_count > 0 && philo->meals_eaten >= rules->must_eat_count)
		{
			pthread_mutex_unlock(&rules->death_mutex);
			break;
		}
		pthread_mutex_unlock(&rules->death_mutex);
		
		// Sleep
		print_status(philo, "is sleeping");
		smart_sleep(rules->time_to_sleep, rules);
		print_status(philo, "is thinking");
		if (philo->id % 2 != 0)
			usleep(500);
	}
	
	return (NULL);
}
