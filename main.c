/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jul <jul@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 16:52:27 by jukerste          #+#    #+#             */
/*   Updated: 2025/07/11 16:54:08 by jul              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_rules	rules;

	if (parse_args(argc, argv, &rules) == 1)
	{
		printf("Error: Invalid arguments\n");
		return (1);
	}
	printf("Philosophers: %d\n", rules.total_philos);
	printf("Time to die: %d\n", rules.time_to_die);
	printf("Time to eat: %d\n", rules.time_to_eat);
	printf("Time to sleep: %d\n", rules.time_to_sleep);
	if (rules.must_eat_count != -1)
		printf("Must eat count: %d\n", rules.must_eat_count);
}
