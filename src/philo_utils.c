/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jul <jul@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 13:08:00 by jukerste          #+#    #+#             */
/*   Updated: 2026/01/13 00:20:45 by jul              ###   ########.fr       */
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
	pthread_mutex_lock(&philo->rules->death_mutex);
	if (philo->rules->philo_died)
	{
		pthread_mutex_unlock(&philo->rules->death_mutex);
		pthread_mutex_unlock(&philo->rules->print_mutex);
		return ;
	}
	timestamp = get_time_in_ms() - philo->rules->start_time;
	printf("%ld %i %s\n", timestamp, philo->id, status);
	pthread_mutex_unlock(&philo->rules->death_mutex);
	pthread_mutex_unlock(&philo->rules->print_mutex);
}

void	smart_sleep(long ms, t_rules *rules)
{
	long	start_time;

	start_time = get_time_in_ms();
	while (1)
	{
		pthread_mutex_lock(&rules->death_mutex);
		if (rules->philo_died)
		{
			pthread_mutex_unlock(&rules->death_mutex);
			break ;
		}
		pthread_mutex_unlock(&rules->death_mutex);
		if (get_time_in_ms() - start_time >= ms)
			break ;
		usleep(500);
	}
}

void	cleanup(t_rules *rules)
{
	int	i;

	if (!rules)
		return ;
	if (rules->philos)
	{
		i = 0;
		while (i < rules->total_philos)
		{
			pthread_mutex_destroy(&rules->forks[i]);
			pthread_mutex_destroy(&rules->philos[i].meal_mutex);
			i++;
		}
	}
	pthread_mutex_destroy(&rules->print_mutex);
	pthread_mutex_destroy(&rules->death_mutex);
	if (rules->forks)
		free(rules->forks);
	if (rules->philos)
		free(rules->philos);
}
