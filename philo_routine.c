/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jul <jul@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 15:00:13 by jukerste          #+#    #+#             */
/*   Updated: 2025/12/21 14:50:44 by jul              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	t_rules	*rules;
	
	philo = (t_philo *)arg;
	rules = philo->rules;
	
	// edge case for when there is only 1 philo
	if (rules->total_philos == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(&rules->death_mutex);
		philo->last_meal_time = get_time_in_ms();
		pthread_mutex_unlock(&rules->death_mutex);
		smart_sleep(rules->time_to_die);
		pthread_mutex_unlock(philo->left_fork);
		return(NULL);
	}
	// 1. delayed start for even ID philos. To prevent deadlock
	if (philo->id % 2 == 0)
		usleep(1000);
	// 2. Main loop checks death at the start of each cycle
	while (is_sim_over(rules) == 0)
	{
		// A. Think
		print_status(philo, "is thinking");
		
		// B. eating logic
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(&rules->death_mutex);
		philo->last_meal_time = get_time_in_ms();
		pthread_mutex_unlock(&rules->death_mutex);
		print_status(philo, "is eating");
		smart_sleep(rules->time_to_eat);
		philo->meals_eaten++;
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		print_status(philo, "is sleeping");
		smart_sleep(rules->time_to_sleep);
	}
	return (NULL);
}
