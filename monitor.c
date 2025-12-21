/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jul <jul@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 16:25:07 by jukerste          #+#    #+#             */
/*   Updated: 2025/12/21 14:24:30 by jul              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor_routine(void *arg)
{
	t_rules	*rules;
	int		i;
	long	current_time;

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
		usleep(1000);
	}
}
