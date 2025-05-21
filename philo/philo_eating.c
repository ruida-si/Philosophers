/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eating.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruida-si <ruida-si@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 12:06:10 by ruida-si          #+#    #+#             */
/*   Updated: 2025/05/21 15:32:55 by ruida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int			read_meals(t_philo *philo);
static void	update_meals(t_philo *philo);
static void	update_last_meal(t_philo *philo);
static int	check_order(t_philo *philo, t_data *data);

void	eating(t_philo *philo, t_data *data)
{
	while (check_finish(data))
	{
		if (check_order(philo, data)
			&& check_fork_status(philo->fork1, philo->fork1_status))
		{
			ft_print(data, FORK, NULL, philo->id);
			if (check_fork_status(philo->fork2, philo->fork2_status))
			{
				update_last_meal(philo);
				ft_print(data, FORK, EAT, philo->id);
				while (ft_get_time() - philo->last_meal < data->time_eat
					&& check_finish(data))
					usleep(500);
				update_meals(philo);
				release_forks(philo->fork1, philo->fork1_status);
				release_forks(philo->fork2, philo->fork2_status);
				break ;
			}
			else
				release_forks(philo->fork1, philo->fork1_status);
		}
		usleep(500);
	}
}

int	read_meals(t_philo *philo)
{
	int	meals;

	meals = 0;
	pthread_mutex_lock(&philo->write_meals);
	meals = philo->meals;
	pthread_mutex_unlock(&philo->write_meals);
	return (meals);
}

static void	update_meals(t_philo *philo)
{
	pthread_mutex_lock(&philo->write_meals);
	philo->meals++;
	pthread_mutex_unlock(&philo->write_meals);
}

static void	update_last_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->write_last_meal);
	philo->last_meal = ft_get_time();
	pthread_mutex_unlock(&philo->write_last_meal);
}

static int	check_order(t_philo *philo, t_data *data)
{
	if (philo->meals == 0)
		return (1);
	else
	{
		if (data->nbr_philo % 2 != 0)
		{
			if (ft_get_time() - philo->last_meal < 3 * data->time_eat)
				return (0);
		}
		else
		{
			if (ft_get_time() - philo->last_meal < 2 * data->time_eat)
				return (0);
		}
	}
	return (1);
}
