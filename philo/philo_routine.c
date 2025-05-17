/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruida-si <ruida-si@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:58:16 by ruida-si          #+#    #+#             */
/*   Updated: 2025/05/17 17:18:47 by ruida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleeping(t_philo *philo, t_data *data);

void	sleeping(t_philo *philo, t_data *data)
{
	long	start;

	start = ft_get_time();
	pthread_mutex_lock(&data->print);
	if (data->finish == 0)
		printf("%ld %i %s\n", ft_get_time() - data->start, philo->n + 1, SLEEP);
	pthread_mutex_unlock(&data->print);
	while (ft_get_time() - start < data->time_sleep && !data->finish)
		usleep(1000);
}
