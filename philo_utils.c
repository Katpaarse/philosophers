/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jukerste <jukerste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 13:08:00 by jukerste          #+#    #+#             */
/*   Updated: 2025/12/02 16:47:29 by jukerste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// project times are in ms. time_to_sleep, time_to_eat etc
long	get_time_in_ms(void)
{
	struct timeval	tv;
	
	gettimeofday(&tv, NULL); // get current time from system
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000); // convert to milliseconds
}

// print mutex one by one so the message stays clear and not printing multiple at a time
void	print_status(t_philo *philo, char *status)
{
	long	timestamp;
	
	pthread_mutex_lock(&philo->rules->print_mutex);
	if (!philo->rules->philo_died) // check if sim is still running
	{
		timestamp = get_time_in_ms() - philo->rules->start_time;
		printf("%ld %i %s\n", timestamp, philo->id, status);
	}
	pthread_mutex_unlock(&philo->rules->print_mutex);
}

// function that checks if philo died ever 0.1 ms. So it doesnt print info that is false when philo died
void	smart_sleep(long milliseconds)
{
	long	start_time;

	start_time = get_time_in_ms();
	while (get_time_in_ms() - start_time < milliseconds)
		usleep(100);
}

// Check if simulation should end (someone died)
int	is_sim_over(t_rules *rules)
{
	int	sim_ended;

	pthread_mutex_lock(&rules->death_mutex);
	sim_ended = rules->philo_died;
	pthread_mutex_unlock(&rules->death_mutex);
	return (sim_ended);
}
