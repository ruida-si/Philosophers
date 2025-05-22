/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruida-si <ruida-si@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 13:42:24 by ruida-si          #+#    #+#             */
/*   Updated: 2025/05/22 11:12:31 by ruida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>

// Colors
# define RED "\033[41m"
# define RESET "\033[0m"

// Fork status
# define FREE 0
# define TAKEN 1

// Actions
# define FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DEAD "died"

typedef struct s_data	t_data;

typedef struct s_philo
{
	int				id;
	int				meals;
	long			last_meal;
	int				fork_sts;
	int				*fork1_status;
	int				*fork2_status;
	pthread_mutex_t	fork;
	pthread_mutex_t	*fork1;
	pthread_mutex_t	*fork2;
	pthread_mutex_t	write_last_meal;
	pthread_mutex_t	write_meals;
	pthread_t		thread;
	t_data			*data;
}	t_philo;

typedef struct s_data
{
	char			*av[5];
	long			start;
	int				nbr_philo;
	long			time_die;
	long			time_eat;
	long			time_sleep;
	int				nbr_meals;
	int				finish;
	pthread_mutex_t	print;
	pthread_mutex_t	write_finish;	
	pthread_t		monitor;
	t_philo			*philo;
}	t_data;

// UTILS INNIT
long	ft_atol(char *s, t_data *data, int j);
long	ft_get_time(void);
void	print_usage(void);
int		innit_data(char **av, t_data *data);

// MONITOR ROUTINE
void	*monitor_routine(void *arg);

// PHILO ROUTINE
void	*philo_routine(void *arg);

// ACTIONS
void	eating(t_philo *philo, t_data *data);

// UTILS
void	ft_print(t_data *data, char *str1, char *str2, int n);
int		check_finish(t_data *data);
int		read_meals(t_philo *philo);
void	release_forks(pthread_mutex_t *fork, int *fork_status);

#endif