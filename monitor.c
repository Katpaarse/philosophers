/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jul <jul@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 16:25:07 by jukerste          #+#    #+#             */
/*   Updated: 2025/12/21 19:08:03 by jul              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor_routine(void *arg)
{
	t_rules	*rules;
	int		i;
	long	current_time;
	int		all_ate_enough;
	
	rules = (t_rules *)arg;
	while (1)
	{
		i = 0;
		while (i < rules->total_philos)
		{
			current_time = get_time_in_ms();
			pthread_mutex_lock(&rules->death_mutex);
			if (current_time - rules->philos[i].last_meal_time > rules->time_to_die)
			{
				rules->philo_died = 1;
				printf("%ld %i died\n", current_time - rules->start_time, rules->philos[i].id);
				pthread_mutex_unlock(&rules->death_mutex);
				return (NULL);
			}
			pthread_mutex_unlock(&rules->death_mutex);
			i++;
		}
		if (rules->must_eat_count != 1)
		{
			all_ate_enough = 1;
			i = 0;
			while (i < rules->total_philos)
			{
				if (rules->philos[i].meals_eaten < rules->must_eat_count)
				{
					all_ate_enough = 0;
					break ;
				}
				i++;
			}
			if (all_ate_enough)
			{
				pthread_mutex_lock(&rules->death_mutex);
				rules->philo_died = 1;
				pthread_mutex_unlock(&rules->death_mutex);
				return (NULL);
			}
		}
		usleep(1000);
	}
}
