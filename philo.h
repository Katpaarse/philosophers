/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jukerste <jukerste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 16:21:50 by jukerste          #+#    #+#             */
/*   Updated: 2025/08/08 15:09:46 by jukerste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>
# include <unistd.h>

struct s_rules;

typedef struct	s_philo
{
	int				id;
	int				meals_eaten;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct	s_rules	*rules;
}	t_philo;

typedef struct s_rules
{
	t_philo			*philos;
	int				total_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_eaten;
	int				must_eat_count;
	int				philo_died;
	long			start_time;
	pthread_mutex_t	*forks;
}	t_rules;

long	ft_atol(char const *str);
int		is_only_digits(char *str);
int		parse_args(int argc, char **argv, t_rules *rules);
int		philosophers_and_forks(t_rules *rules);
void	*philo_routine(void *arg);

#endif