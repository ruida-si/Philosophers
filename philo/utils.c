/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruida-si <ruida-si@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 15:13:44 by ruida-si          #+#    #+#             */
/*   Updated: 2025/05/20 14:00:27 by ruida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long		ft_get_time(void);
void		print_usage(void);
long		ft_atol(char *s, t_data *data, int j);
static int	white_spaces(char c);

void	ft_print(t_data *data, char *str1, char *str2, int n)
{
	pthread_mutex_lock(&data->print);
	if (check_finish(data))
	{
		printf("%ld %i %s\n", ft_get_time() - data->start, n + 1, str1);
		if (str2)
			printf("%ld %i %s\n", ft_get_time() - data->start, n + 1, str2);
	}
	pthread_mutex_unlock(&data->print);
}

long	ft_get_time(void)
{
	struct timeval	tv;
	long			n;

	if (gettimeofday(&tv, NULL) != 0)
		return (printf("Error gettimeofday()\n"), -1);
	n = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (n);
}

void	print_usage(void)
{
	printf("\nYou should pass FOUR or FIVE arguments to the program\n"
		"Example:\n"
		"[0] Program name\n"
		"[1] Number of Philosophers\n"
		"[2] Time to die\n"
		"[3] Time to eat\n"
		"[4] Time to sleep\n"
		"[5] [optional] Number_of_times_each_philosopher_must_eat\n\n");
}

long	ft_atol(char *s, t_data *data, int j)
{
	int		i;
	long	n;

	n = 0;
	i = 0;
	if (!s || !s[i])
		return (data->av[j] = "Void argument", -1);
	while (s[i] == ' ' || white_spaces(s[i]))
		i++;
	if (s[i] == '-')
		return (data->av[j] = "Only positive numbers", -1);
	if (s[i] == '+')
		i++;
	while (s[i] >= '0' && s[i] <= '9')
	{
		n = n * 10 + (s[i] - '0');
		if (n > INT_MAX)
			return (data->av[j] = "Number is higher than INT_MAX", -1);
		i++;
	}
	if (s[i])
		return (data->av[j] = "Invalid argument", -1);
	if (n == 0)
		return (data->av[j] = "Only numbers > 0", -1);
	return (n);
}

static int	white_spaces(char c)
{
	if (c >= 9 && c <= 13)
		return (1);
	return (0);
}
