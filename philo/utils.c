/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruida-si <ruida-si@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 15:13:44 by ruida-si          #+#    #+#             */
/*   Updated: 2025/05/06 19:35:37 by ruida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int			ft_atoi(char *s);
int			print_error(char *s);
static int	white_spaces(char c);
static int	ft_strlen(char *s);


void	free_mem(pthread_t *td, pthread_mutex_t *mutex)
{
	free(td);
	pthread_mutex_destroy(mutex);
}

int	ft_atoi(char *s)
{
	int		i;
	long	n;

	n = 0;
	i = 0;
	if (!s || !s[i])
		return (print_error("Void arguments"));
	while (s[i] == ' ' || white_spaces(s[i]))
		i++;
	if (s[i] == '-')
		return (print_error("Only positive numbers"));
	if (s[i] == '+')
		i++;
	while (s[i] >= '0' && s[i] <= '9')
	{
		n = n * 10 + (s[i] - '0');
		if (n > INT_MAX)
			return (print_error("Number is higher than INT_MAX"));
		i++;
	}
	if (i < ft_strlen(s))
		return (print_error("Invalid arguments"));
	if (n == 0)
		return (print_error("Only numbers > 0"));
	return (n);
}

int	print_error(char *s)
{
	printf("%s\n", s);
	return (-1);
}

static int  white_spaces(char c)
{
	if (c >= 9 && c <= 13)
		return (1);
	return (0);
}

static int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}
