/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jul <jul@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 16:21:50 by jukerste          #+#    #+#             */
/*   Updated: 2026/01/05 02:49:59 by jul              ###   ########.fr       */
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
	long			last_meal_time;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t meal_mutex;
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
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	death_mutex;
}	t_rules;

long	ft_atol(char const *str);
int		is_only_digits(char *str);
int		parse_args(int argc, char **argv, t_rules *rules);
int		philosophers_and_forks(t_rules *rules);
void	*philo_routine(void *arg);
long	get_time_in_ms(void);
void	print_status(t_philo *philo, char *status);
void	smart_sleep(long ms, t_rules *rules);
int		is_sim_over(t_rules *rules);
void	*monitor_routine(void *arg);
void	cleanup(t_rules *rules);
void	init_rules(t_rules *rules);

#endif