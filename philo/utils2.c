/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruida-si <ruida-si@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 17:39:44 by ruida-si          #+#    #+#             */
/*   Updated: 2025/05/20 17:49:41 by ruida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	one_routine(t_data *data)
{
	printf("%ld %i %s\n", ft_get_time() - data->start, 1, FORK);
	usleep(data->time_die * 1000);
	printf("%ld %i %s\n", ft_get_time() - data->start, 1, DEAD);
	return (0);
}
