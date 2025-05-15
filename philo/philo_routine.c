/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruida-si <ruida-si@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:58:16 by ruida-si          #+#    #+#             */
/*   Updated: 2025/05/13 18:27:58 by ruida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_philo *philo, t_data *data);
void	sleeping(t_philo *philo, t_data *data);

void	eating(t_philo *philo, t_data *data)
{
	int				n;
	pthread_mutex_t	fork2;
	
	n = philo->n;
	fork2 = data->philo[(n + 1) % data->nbr_philo].fork;	
	while (data->finish == 0)
	{
		if (!pthread_mutex_lock(&philo->fork))
		{
			if (!pthread_mutex_lock(&fork2))
			{
				philo->last_meal = ft_get_time();
				pthread_mutex_lock(&data->print);
				printf("%ld %i has taken a fork\n", ft_get_time() - data->start, n + 1);
				printf("%ld %i has taken a fork\n", ft_get_time() - data->start, n + 1);
				printf("%ld %i is eating\n", ft_get_time() - data->start, n + 1);
				pthread_mutex_unlock(&data->print);				
				while (ft_get_time() - philo->last_meal < data->time_eat)
					usleep(500);
				philo->meals++;
				pthread_mutex_unlock(&philo->fork);
				pthread_mutex_unlock(&fork2);
				break ;
			}
			else
				pthread_mutex_unlock(&philo->fork);
		}
		usleep(500);
	}
}

void	sleeping(t_philo *philo, t_data *data)
{
	long	start;

	start = ft_get_time();
	pthread_mutex_lock(&data->print);
	if (data->finish == 0)
		printf("%ld %i is sleeping\n", ft_get_time() - data->start, philo->n + 1);
	pthread_mutex_unlock(&data->print);
	while (ft_get_time() - start < data->time_sleep)
		usleep(500);
}
