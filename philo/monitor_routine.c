/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruida-si <ruida-si@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 17:01:40 by ruida-si          #+#    #+#             */
/*   Updated: 2025/05/17 20:54:39 by ruida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_for_dead(t_data *data);

int	check_nbr_meals(t_data *data)
{
	int	i;
	int	a;

	i = 0;
	a = 0;
	if (data->nbr_meals > 0)
	{
		while (i < data->nbr_philo)
		{
			if (data->philo[i].meals < data->nbr_meals)
				a = 1;
			i++;
		}
		if (a == 0)
		{
			data->finish = 1;
			return (0);
		}
	}
	return (1);
}

int	check_for_dead(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_philo)
	{
		if (ft_get_time() - data->philo[i].last_meal > data->time_die)
		{
			data->finish = 1;
			pthread_mutex_lock(&data->print);
			printf("%ld %i %s\n", ft_get_time() - data->start, i + 1, DEAD);			
			pthread_mutex_unlock(&data->print);		
			return (0);
		}
		i++;
	}
	return (1);
}
