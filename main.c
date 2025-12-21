/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jul <jul@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 16:52:27 by jukerste          #+#    #+#             */
/*   Updated: 2025/12/21 19:11:55 by jul              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_rules		rules;
	pthread_t	monitor;
	int			i;

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
	rules.start_time = get_time_in_ms();
	i = 0;
	while (i < rules.total_philos)
	{
		pthread_mutex_lock(&rules.death_mutex);
		rules.philos[i].last_meal_time = rules.start_time;
		pthread_mutex_unlock(&rules.death_mutex);
		i++;
	}
	if (pthread_create(&monitor, NULL, monitor_routine, &rules) != 0)
	{
		cleanup(&rules);
		return (1);
	}
	i = 0;
	while (i < rules.total_philos)
	{
		if (pthread_create(&rules.philos[i].thread, NULL, philo_routine, &rules.philos[i]) != 0)
		{
			printf("Error: Failed to create philosopher thread\n");
			pthread_mutex_destroy(&rules.death_mutex);
			rules.philo_died = 1;
			pthread_mutex_unlock(&rules.death_mutex);
			pthread_join(monitor, NULL);
			cleanup(&rules);
			return (1);
		}
		i++;
	}
	pthread_join(monitor, NULL);
	i = 0;
	while (i < rules.total_philos)
	{
		pthread_join(rules.philos[i].thread, NULL);
		i++;
	}
	i = 0;
	while (i < rules.total_philos)
	{
		pthread_mutex_destroy(&rules.forks[i]);
		i++;
	}
	pthread_mutex_destroy(&rules.print_mutex);
	pthread_mutex_destroy(&rules.death_mutex);
	free(rules.forks);
	free(rules.philos);
	return (0);
}
