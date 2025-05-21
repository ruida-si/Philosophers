/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruida-si <ruida-si@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 17:01:40 by ruida-si          #+#    #+#             */
/*   Updated: 2025/05/21 13:17:54 by ruida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_nbr_meals(t_data *data);
static int	check_for_dead(t_data *data);
static void	update_finish(t_data *data);
static long	read_last_meal(t_philo *philo);

void	*monitor_routine(void *arg)
{
	t_data	*data;
	int		i;

	i = 0;
	data = (t_data *)arg;
	usleep(0.95 * data->time_die * 1000);
	while (1)
	{
		if (!check_nbr_meals(data))
			break ;
		if (!check_for_dead(data))
			break ;
		usleep(500);
	}
	return (NULL);
}

static int	check_nbr_meals(t_data *data)
{
	int	i;
	int	a;

	i = 0;
	a = 0;
	if (data->nbr_meals > 0)
	{
		while (i < data->nbr_philo)
		{
			if (read_meals(&data->philo[i]) < data->nbr_meals)
				a = 1;
			i++;
		}
		if (a == 0)
		{
			update_finish(data);
			return (0);
		}
	}
	return (1);
}

static int	check_for_dead(t_data *data)
{
	int		i;
	long	curr_time;

	i = 0;
	curr_time = ft_get_time();
	while (i < data->nbr_philo)
	{
		if (curr_time - read_last_meal(&data->philo[i]) > data->time_die)
		{
			update_finish(data);
			pthread_mutex_lock(&data->print);
			printf("%ld %i %s\n", curr_time - data->start, i + 1, DEAD);
			pthread_mutex_unlock(&data->print);
			return (0);
		}
		i++;
	}
	return (1);
}

static void	update_finish(t_data *data)
{
	pthread_mutex_lock(&data->write_finish);
	data->finish = 1;
	pthread_mutex_unlock(&data->write_finish);
}

static long	read_last_meal(t_philo *philo)
{
	long	last_meal;

	pthread_mutex_lock(&philo->write_last_meal);
	last_meal = philo->last_meal;
	pthread_mutex_unlock(&philo->write_last_meal);
	return (last_meal);
}
