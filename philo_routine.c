/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jukerste <jukerste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 15:00:13 by jukerste          #+#    #+#             */
/*   Updated: 2025/12/02 17:43:08 by jukerste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	t_rules	*rules;
	
	philo = (t_philo *)arg;
	rules = philo->rules;

	if (rules->total_philos == 1)
	{
		
	}
	
	printf("Philosopher %d is thinking\n", philo->id);
	usleep(500000);
	return (NULL);
}
