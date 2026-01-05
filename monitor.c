/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jul <jul@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 16:25:07 by jukerste          #+#    #+#             */
/*   Updated: 2026/01/05 03:03:31 by jul              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor_routine(void *arg)
{
	t_rules	*rules;
	int		i;
	long	current_time;
	int		all_ate;
	
	rules = (t_rules *)arg;
	
	while (1)
	{
		i = 0;
		all_ate = 1;
		
		// Rapidly check all philosophers
		while (i < rules->total_philos)
		{
			current_time = get_time_in_ms();
			
			pthread_mutex_lock(&rules->death_mutex);
			
			// Check for death
			if (current_time - rules->philos[i].last_meal_time >= rules->time_to_die)
			{
				rules->philo_died = 1;
				pthread_mutex_unlock(&rules->death_mutex);
				
				pthread_mutex_lock(&rules->print_mutex);
				printf("%ld %i died\n", current_time - rules->start_time, rules->philos[i].id);
				pthread_mutex_unlock(&rules->print_mutex);
				return (NULL);
			}
			
			// Check meals
			if (rules->must_eat_count != -1 && 
				rules->philos[i].meals_eaten < rules->must_eat_count)
			{
				all_ate = 0;
			}
			
			pthread_mutex_unlock(&rules->death_mutex);
			i++;
		}
		
		// Check if all have eaten enough
		if (rules->must_eat_count != -1 && all_ate)
		{
			pthread_mutex_lock(&rules->death_mutex);
			rules->philo_died = 1;
			pthread_mutex_unlock(&rules->death_mutex);
			return (NULL);
		}
		usleep(100);
	}
	return (NULL);
}
