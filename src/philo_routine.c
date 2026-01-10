/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jukerste <jukerste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 15:00:13 by jukerste          #+#    #+#             */
/*   Updated: 2026/01/06 17:22:00 by jukerste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal_time = get_time_in_ms();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_mutex);
	print_status(philo, "is eating");
	smart_sleep(philo->rules->time_to_eat, philo->rules);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

static int	grab_even(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(&philo->rules->death_mutex);
	if (philo->rules->philo_died)
	{
		pthread_mutex_unlock(&philo->rules->death_mutex);
		pthread_mutex_unlock(philo->right_fork);
		return (0);
	}
	pthread_mutex_unlock(&philo->rules->death_mutex);
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, "has taken a fork");
	return (1);
}

static int	grab_odd(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(&philo->rules->death_mutex);
	if (philo->rules->philo_died)
	{
		pthread_mutex_unlock(&philo->rules->death_mutex);
		pthread_mutex_unlock(philo->left_fork);
		return (0);
	}
	pthread_mutex_unlock(&philo->rules->death_mutex);
	pthread_mutex_lock(philo->right_fork);
	print_status(philo, "has taken a fork");
	return (1);
}

static int	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
		return (grab_even(philo));
	else
		return (grab_odd(philo));
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	t_rules	*rules;

	philo = (t_philo *)arg;
	rules = philo->rules;
	if (rules->total_philos == 1)
		return (single_philo_case(philo));
	if (philo->id % 2 == 0)
		usleep(15000);
	while (1)
	{
		pthread_mutex_lock(&rules->death_mutex);
		if (rules->philo_died)
			return (pthread_mutex_unlock(&rules->death_mutex), NULL);
		pthread_mutex_unlock(&rules->death_mutex);
		if (!take_forks(philo))
			break ;
		philo_eat(philo);
		print_status(philo, "is sleeping");
		smart_sleep(rules->time_to_sleep, rules);
		print_status(philo, "is thinking");
		if (rules->total_philos % 2 != 0)
			usleep(500);
	}
	return (NULL);
}
