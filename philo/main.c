/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruida-si <ruida-si@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 13:32:11 by ruida-si          #+#    #+#             */
/*   Updated: 2025/05/21 16:09:04 by ruida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	create_threads(t_data *data);
static void	ft_destroy_forks(t_data *data);

int	main(int ac, char **av)
{
	t_data	data;

	if (ac == 5 || ac == 6)
	{
		if (!innit_data(av, &data))
			return (1);
		if (!create_threads(&data))
		{
			ft_destroy_forks(&data);
			free(data.philo);
			return (3);
		}
		ft_destroy_forks(&data);
		free(data.philo);
	}
	else
		print_usage();
	return (0);
}

static int	create_threads(t_data *data)
{
	int	i;

	i = 0;
	if (pthread_create(&data->monitor, NULL, &monitor_routine, data) != 0)
		return (0);
	while (i < data->nbr_philo)
	{
		if (pthread_create(&data->philo[i].thread, NULL, &philo_routine,
				&data->philo[i]) != 0)
			return (0);
		i++;
	}
	i = 0;
	while (i < data->nbr_philo)
	{
		if (pthread_join(data->philo[i].thread, NULL) != 0)
			return (0);
		i++;
	}
	if (pthread_join(data->monitor, NULL) != 0)
		return (0);
	return (1);
}

static void	ft_destroy_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_philo)
	{
		pthread_mutex_destroy(&data->philo[i].fork);
		pthread_mutex_destroy(&data->philo[i].write_last_meal);
		pthread_mutex_destroy(&data->philo[i].write_meals);
		i++;
	}
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->write_finish);
}
