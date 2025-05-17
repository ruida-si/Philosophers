/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruida-si <ruida-si@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 13:42:24 by ruida-si          #+#    #+#             */
/*   Updated: 2025/05/17 21:18:06 by ruida-si         ###   ########.fr       */
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

// colors
# define RED "\033[41m"
# define RESET "\033[0m"

//strings
# define FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DEAD "died"

typedef struct s_data	t_data;

typedef struct s_philo
{
	int				n;
	int				meals;
	long			last_meal;
	pthread_mutex_t	fork;
	pthread_mutex_t	*fork1;
	pthread_mutex_t	*fork2;
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
	long			delay;
	pthread_mutex_t	print;
	pthread_t		monitor;
	t_philo			*philo;
}	t_data;

long	ft_atol(char *s, t_data *data, int j);
int		print_error(char *s);
long	ft_get_time(void);
void	print_usage(void);
int		innit_data(char **av, t_data *data);

// monitor routine
int		check_for_dead(t_data *data);
int		check_nbr_meals(t_data *data);

// eating
void	eating(t_philo *philo, t_data *data);

// sleeping
void	sleeping(t_philo *philo, t_data *data);

#endif