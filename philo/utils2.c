/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruida-si <ruida-si@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 17:39:44 by ruida-si          #+#    #+#             */
/*   Updated: 2025/05/21 16:01:06 by ruida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		check_fork_status(pthread_mutex_t *fork, int *fork_status);
void	release_forks(pthread_mutex_t *fork, int *fork_status);

int	check_fork_status(pthread_mutex_t *fork, int *fork_status)
{
	int	i;

	i = 0;
	pthread_mutex_lock(fork);
	if (*fork_status == FREE)
	{
		i = 1;
		*fork_status = TAKEN;
	}
	pthread_mutex_unlock(fork);
	return (i);
}

void	release_forks(pthread_mutex_t *fork, int *fork_status)
{
	pthread_mutex_lock(fork);
	*fork_status = FREE;
	pthread_mutex_unlock(fork);
}
