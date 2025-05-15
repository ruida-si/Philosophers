/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruida-si <ruida-si@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 13:32:11 by ruida-si          #+#    #+#             */
/*   Updated: 2025/05/13 18:04:04 by ruida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*philo_routine(void *arg);
static void	*monitor_routine(void *arg);
static int	create_threads(t_data *data);

int	main(int ac, char **av)
{
	t_data	data;

	if (ac == 5 || ac == 6)
	{
		if (!innit_data(av, &data))
			return (1);
		pthread_mutex_init(&data.print, NULL);
		if (!create_threads(&data))
			return (3);
		pthread_mutex_destroy(&data.print);
	}
	else
		print_usage();
	return (0);
}

static void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		eating(philo, philo->data);
		sleeping(philo, philo->data);
	}
	return (NULL);
}

static void	*monitor_routine(void *arg)
{
	t_data	*data;
	int		i;

	i = 0;
	data = (t_data *)arg;
	while (1)
	{
		if (!check_nbr_meals(data))
			break ;
		if (!check_all_dead(data))
			break ;
		usleep(500);
	}
	return (NULL);
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
