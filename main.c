/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jukerste <jukerste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 16:52:27 by jukerste          #+#    #+#             */
/*   Updated: 2025/08/08 15:58:33 by jukerste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_rules	rules;
	int	i;

	if (parse_args(argc, argv, &rules) == 1)
	{
		printf("Error: Invalid arguments\n");
		return (1);
	}
	if (philosophers_and_forks(&rules) == 1)
	{
		printf("Error: Failed to initialize philosophers and forks");
		return (1);
	}
	i = 0;
	while (i < rules.total_philos)
	{
		if (pthread_create(&rules.philos[i].thread, NULL, philo_routine, &rules.philos[i]) != 0)
		{
			printf("Error: Thread creation failed");
			return (1);
		}
		i++;
	}
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
	printf("Philosophers: %d\n", rules.total_philos);
	printf("Time to die: %d\n", rules.time_to_die);
	printf("Time to eat: %d\n", rules.time_to_eat);
	printf("Time to sleep: %d\n", rules.time_to_sleep);
	if (rules.must_eat_count != -1)
		printf("Must eat count: %d\n", rules.must_eat_count);
	free(rules.forks);
	free(rules.philos);
	return (0);
}
