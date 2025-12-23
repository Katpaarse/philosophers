/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jukerste <jukerste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 13:08:00 by jukerste          #+#    #+#             */
/*   Updated: 2025/12/23 18:25:05 by jukerste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time_in_ms(void)
{
	struct timeval	tv;
	
	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	print_status(t_philo *philo, char *status)
{
	long	timestamp;
	
	pthread_mutex_lock(&philo->rules->print_mutex);
	if (!philo->rules->philo_died)
	{
		timestamp = get_time_in_ms() - philo->rules->start_time;
		printf("%ld %i %s\n", timestamp, philo->id, status);
	}
	pthread_mutex_unlock(&philo->rules->print_mutex);
}

void	smart_sleep(long ms)
{
	long	start_time;

	start_time = get_time_in_ms();
	while (get_time_in_ms() - start_time < ms)
		usleep(100);
}

int	is_sim_over(t_rules *rules)
{
	int	sim_ended;

	pthread_mutex_lock(&rules->death_mutex);
	sim_ended = rules->philo_died;
	pthread_mutex_unlock(&rules->death_mutex);
	return (sim_ended);
}

void	cleanup(t_rules *rules)
{
	int	i;

	if (!rules)
		return ;
	if (rules->forks)
	{
		i = 0;
		while (i < rules->total_philos)
		{
			pthread_mutex_destroy(&rules->forks[i]);
			i++;
		}
	}
	pthread_mutex_destroy(&rules->print_mutex);
	pthread_mutex_destroy(&rules->death_mutex);
}
