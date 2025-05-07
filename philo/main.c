/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruida-si <ruida-si@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 13:32:11 by ruida-si          #+#    #+#             */
/*   Updated: 2025/05/06 19:36:52 by ruida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*philo_routine(void *arg);
static void	*monitor(void *arg);
static int	create_threads(int n, pthread_t *td);
static int innit_data(char **av, t_data *data);

int main(int ac, char **av)
{
	t_data			data;
	pthread_t		*td;
	pthread_mutex_t	mutex;
	
	td = NULL;
	if (ac == 5 || ac == 6)
	{
		if (!innit_data(av, &data))
			return (1);
		td = malloc(sizeof(pthread_t) * (data.nbr_philo + 1));
		pthread_mutex_init(&mutex, NULL);
		if (!create_threads(data.nbr_philo + 1, td))
			return (free_mem(td, &mutex), 2);
		pthread_mutex_destroy(&mutex);		
		free(td);
	}
	else
	{
		printf("Error -> Usage: philosophers time_die time_eat time_sleep"
		" [number_meals]\n");
	}	
	return (0);
}

static void	*philo_routine(void *arg)
{
	(void)arg;
	printf("Eating\n");
	sleep(3);
	printf("Finish\n");
	return (NULL);
}

static void	*monitor(void *arg)
{
	(void)arg;
	printf("Check for dead Philosophers\n");
	return (NULL);
}

static int	create_threads(int n, pthread_t *td)
{
	int i;

	i = 0;
	while (i < n)
	{
		if (i == n -1)
		{
			if (pthread_create(&td[i], NULL, &monitor, NULL) != 0)
				return (0);
		}
		else
		{
			if (pthread_create(&td[i], NULL, &philo_routine, NULL) != 0)
				return (0);
		}
		i++;
	}
	i = 0;
	while (i < n)
	{
		if (pthread_join(td[i], NULL) != 0)
			return (0);
		i++;
	}
	return (1);
}

static int innit_data(char **av, t_data *data)
{
	data->nbr_philo = ft_atoi(av[1]);
	if (data->nbr_philo == -1)
		return (0);
	data->time_die = ft_atoi(av[2]);
	if (data->time_die == -1)
		return (0);
	data->time_eat = ft_atoi(av[3]);
	if (data->time_eat == -1)
		return (0);
	data->time_sleep = ft_atoi(av[4]);
	if (data->time_sleep == -1)
		return (0);
	if (av[5])
	{
		data->nbr_meals = ft_atoi(av[5]);
		if (data->nbr_meals == -1)
			return (0);
	}
	else
		data->nbr_meals = -1;
	return (1);
}
