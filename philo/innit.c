/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   innit.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruida-si <ruida-si@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 17:36:14 by ruida-si          #+#    #+#             */
/*   Updated: 2025/05/13 13:59:19 by ruida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_philo(t_data *data);
static int	check_errors(t_data *data);
static void	print_msg(int fail, t_data *data);

int	innit_data(char **av, t_data *data)
{
	data->start = ft_get_time();
	data->nbr_philo = ft_atol(av[1], data, 0);
	if (data->nbr_philo > 200)
	{
		data->av[0] = "Number of philosophers > 0 and < 201";
		data->nbr_philo = -1;
	}
	data->time_die = ft_atol(av[2], data, 1);
	data->time_eat = ft_atol(av[3], data, 2);
	data->time_sleep = ft_atol(av[4], data, 3);
	data->finish = 0;
	if (av[5])
		data->nbr_meals = ft_atol(av[5], data, 4);
	else
		data->nbr_meals = -2;
	if (!check_errors(data))
		return (0);
	if (!init_philo(data))
		return (0);
	return (1);
}

static int	init_philo(t_data *data)
{
	int	i;

	i = 0;
	data->philo = malloc(sizeof(t_philo) * (data->nbr_philo));
	if (!data->philo)
	{
		printf("Error Malloc\n");
		return (0);
	}
	while (i < data->nbr_philo)
	{
		data->philo[i].n = i;
		data->philo[i].meals = 0;
		data->philo[i].last_meal = ft_get_time();
		data->philo[i].dead = 0;
		data->philo[i].data = data;
		pthread_mutex_init(&data->philo[i].fork, NULL);
		i++;			
	}
	return (1);
}

static int	check_errors(t_data *data)
{
	int	fail;

	fail = 0;
	if (data->start == -1)
		fail |= (1 << 0);
	if (data->nbr_philo == -1)
		fail |= (1 << 1);
	if (data->time_die == -1)
		fail |= (1 << 2);
	if (data->time_eat == -1)
		fail |= (1 << 3);
	if (data->time_sleep == -1)
		fail |= (1 << 4);
	if (data->nbr_meals == -1)
		fail |= (1 << 5);	
	if (fail)
	{
		print_msg(fail, data);
		return (0);
	}
	else
		return (1);
}

static void	print_msg(int fail, t_data *data)
{
	if (fail & (1 << 0))
		printf(RED"Start time failed\n"RESET);
	if (fail & (1 << 1))
		printf(RED"[1] Nbr_philo failed:"RESET" %s\n", data->av[0]);
	if (fail & (1 << 2))
		printf(RED"[2] Time_die failed:"RESET" %s\n", data->av[1]);
	if (fail & (1 << 3))
		printf(RED"[3] Time_eat failed:"RESET" %s\n", data->av[2]);
	if (fail & (1 << 4))
		printf(RED"[4] Time_sleep failed:"RESET" %s\n", data->av[3]);
	if (fail & (1 << 5))
		printf(RED"[5] Nbr_meals failed:"RESET" %s\n", data->av[4]);
}
