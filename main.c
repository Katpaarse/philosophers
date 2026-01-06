/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jukerste <jukerste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 16:52:27 by jukerste          #+#    #+#             */
/*   Updated: 2026/01/06 15:44:36 by jukerste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	start_simulation(t_rules *rules, pthread_t *monitor)
{
	int	i;

	rules->start_time = get_time_in_ms();
	i = 0;
	while (i < rules->total_philos)
	{
		pthread_mutex_lock(&rules->philos[i].meal_mutex);
		rules->philos[i].last_meal_time = rules->start_time;
		pthread_mutex_unlock(&rules->philos[i].meal_mutex);
		i++;
	}
	i = 0;
	while (i < rules->total_philos)
	{
		if (pthread_create(&rules->philos[i].thread, NULL,
				philo_routine, &rules->philos[i]) != 0)
			return (1);
		i++;
	}
	if (pthread_create(monitor, NULL, monitor_routine, rules) != 0)
		return (1);
	return (0);
}

static void	stop_simulation(t_rules *rules, pthread_t monitor)
{
	int	i;

	pthread_join(monitor, NULL);
	i = 0;
	while (i < rules->total_philos)
	{
		pthread_join(rules->philos[i].thread, NULL);
		i++;
	}
	cleanup(rules);
}

int	main(int argc, char **argv)
{
	t_rules		rules;
	pthread_t	monitor;

	init_rules(&rules);
	if (parse_args(argc, argv, &rules) == 1)
	{
		printf("Error: Invalid arguments\n");
		return (1);
	}
	if (philosophers_and_forks(&rules) == 1)
	{
		printf("Error: Failed to initialize philosophers and forks\n");
		return (1);
	}
	if (start_simulation(&rules, &monitor) != 0)
	{
		pthread_mutex_lock(&rules.death_mutex);
		rules.philo_died = 1;
		pthread_mutex_unlock(&rules.death_mutex);
	}
	stop_simulation(&rules, monitor);
	return (0);
}
