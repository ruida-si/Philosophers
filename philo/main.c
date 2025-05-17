/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruida-si <ruida-si@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 13:32:11 by ruida-si          #+#    #+#             */
/*   Updated: 2025/05/17 21:03:09 by ruida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_destroy_forks(t_data *data);
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
		ft_destroy_forks(&data);
	}
	else
		print_usage();
	return (0);
}

static void	ft_destroy_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_philo)
	{
		pthread_mutex_destroy(&data->philo[i].fork);
		i++;		
	}	
}

static void	*philo_routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;
	
	philo = (t_philo *)arg;
	data = philo->data;	
	while (data->finish == 0)
	{
		if (data->finish == 0)
			eating(philo, philo->data);
		if (data->finish == 0)
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
		if (!check_for_dead(data))
			break ;
		usleep(1000);
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
