/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruida-si <ruida-si@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 17:39:44 by ruida-si          #+#    #+#             */
/*   Updated: 2025/05/21 16:17:42 by ruida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	release_forks(pthread_mutex_t *fork, int *fork_status);

int	read_meals(t_philo *philo)
{
	int	meals;

	meals = 0;
	pthread_mutex_lock(&philo->write_meals);
	meals = philo->meals;
	pthread_mutex_unlock(&philo->write_meals);
	return (meals);
}

void	release_forks(pthread_mutex_t *fork, int *fork_status)
{
	pthread_mutex_lock(fork);
	*fork_status = FREE;
	pthread_mutex_unlock(fork);
}
