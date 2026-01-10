/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jukerste <jukerste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 17:22:37 by jukerste          #+#    #+#             */
/*   Updated: 2026/01/06 17:22:44 by jukerste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*single_philo_case(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, "has taken a fork");
	smart_sleep(philo->rules->time_to_die, philo->rules);
	pthread_mutex_unlock(philo->left_fork);
	return (NULL);
}
