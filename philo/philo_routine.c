/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruida-si <ruida-si@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:58:16 by ruida-si          #+#    #+#             */
/*   Updated: 2025/05/20 15:13:46 by ruida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	check_first_iter(t_philo *philo, t_data *data, long delay);
int			check_finish(t_data *data);
static void	sleeping(t_philo *philo, t_data *data);
static void	thinking(t_philo *philo, t_data *data);

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;
	long	delay;

	philo = (t_philo *)arg;
	data = philo->data;
	delay = data->time_eat * 1000;
	check_first_iter(philo, data, delay);
	while (check_finish(data))
	{
		if (check_finish(data))
			eating(philo, philo->data);
		if (check_finish(data))
			sleeping(philo, philo->data);
		if (check_finish(data))
			thinking(philo, philo->data);
	}
	return (NULL);
}

static void	check_first_iter(t_philo *philo, t_data *data, long delay)
{
	if (data->nbr_philo % 2 != 0)
	{
		if (philo->n % 2 != 0 || data->nbr_philo == 1)
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

int	check_finish(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&data->write);
	if (data->finish == 0)
		i = 1;
	pthread_mutex_unlock(&data->write);
	return (i);
}

static void	sleeping(t_philo *philo, t_data *data)
{
	long	start;
	int		n;

	n = philo->n;
	start = ft_get_time();
	pthread_mutex_lock(&data->print);
	if (check_finish(data))
		printf("%ld %i %s\n", ft_get_time() - data->start, n + 1, SLEEP);
	pthread_mutex_unlock(&data->print);
	while (ft_get_time() - start < data->time_sleep && check_finish(data))
		usleep(500);
}

static void	thinking(t_philo *philo, t_data *data)
{
	int	n;

	n = philo->n;
	pthread_mutex_lock(&data->print);
	if (check_finish(data))
		printf("%ld %i %s\n", ft_get_time() - data->start, n + 1, THINK);
	pthread_mutex_unlock(&data->print);
}
