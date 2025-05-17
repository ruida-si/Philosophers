/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eating.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruida-si <ruida-si@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 12:06:10 by ruida-si          #+#    #+#             */
/*   Updated: 2025/05/17 20:28:11 by ruida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_print(t_data *data, char *str1, char *str2, int n);
static void	check_first_iter(t_philo *philo, t_data *data);
static int	check_order(t_philo *philo, t_data * data);

void	eating(t_philo *philo, t_data *data)
{
	int	n;

	n = philo->n;
	check_first_iter(philo, data);
	while (data->finish == 0)
	{
		if (check_order(philo, data) && !pthread_mutex_lock(philo->fork1))
		{
			ft_print(data, FORK, NULL, philo->n);
			if (!pthread_mutex_lock(philo->fork2))
			{
				philo->last_meal = ft_get_time();
				ft_print(data, FORK, EAT, philo->n);			
				while (ft_get_time() - philo->last_meal < data->time_eat && !data->finish)
					usleep(500);
				philo->meals++;
				pthread_mutex_unlock(philo->fork1);
				pthread_mutex_unlock(philo->fork2);
				break ;
			}
			else
				pthread_mutex_unlock(philo->fork1);
		}
		usleep(1000);
	}
}

static int	check_order(t_philo *philo, t_data *data)
{
	long	cur_time;
	
	cur_time = ft_get_time();
	if (philo->meals == 0)
		return (1);
	else
	{
		if (data->nbr_philo % 2 != 0)
		{
			if (cur_time - philo->last_meal < 0.9 * 3 * data->time_eat)
				return (0);
		}
		else
		{
			if (cur_time - philo->last_meal < 0.9 * 2 * data->time_eat)
				return (0);
		}
	}
	return (1);
}

static void	check_first_iter(t_philo *philo, t_data *data)
{
	long	delay;
	
	delay = 0.9 * data->time_eat * 1000;
	if (ft_get_time() - data->start < data->time_eat)
	{
		if (data->nbr_philo % 2 != 0)
		{
			if (philo->n % 2 != 0)
				return ;
			else
			{
				ft_print(data, THINK, NULL, philo->n);
				if (philo->n == data->nbr_philo - 1)
					usleep(delay);
				else
					usleep(2 * delay);
			}
		}
		else
		{
			if (philo->n % 2 != 0)
				return ;
			else
			{
				ft_print(data, THINK, NULL, philo->n);
				usleep(delay);
			}
		}		
	}	
}

static void	ft_print(t_data *data, char *str1, char *str2, int n)
{
	pthread_mutex_lock(&data->print);
	if (data->finish == 0)
	{
		printf("%ld %i %s\n", ft_get_time() - data->start, n + 1, str1);
		if (str2)
			printf("%ld %i %s\n", ft_get_time() - data->start, n + 1, str2);
	}
	pthread_mutex_unlock(&data->print);	
}
