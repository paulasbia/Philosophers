/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 09:50:30 by paulabiazot       #+#    #+#             */
/*   Updated: 2023/11/08 16:36:20 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long int	ft_atoi(const char *nptr)
{
	int			signal;
	long int	result;

	signal = 1;
	result = 0;
	while (*nptr == ' ' || (*nptr >= 9 && *nptr <= 13))
		nptr++;
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			signal = signal * -1;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		result = result * 10 + (*nptr - '0');
		nptr++;
	}
	return ((long int)result * signal);
}

int	is_number(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int	just_one(char **av)
{
	if (ft_atoi(av[1]) == 1)
	{
		printf("\033[32m%i %d took a fork\n\e[0m", 0, 1);
		usleep(ft_atoi(av[2]) * 1000);
		printf("\033[91m%li %d died\n\e[0m", ft_atoi(av[2]) + 1, 1);
		return (1);
	}
	return (0);
}

void	msg(t_philo *philo, struct timeval *time, int action)
{
	pthread_mutex_lock(&philo->start->mutex.is_death);
	if (philo->start->death > 0 && philo->start->death != philo->content)
	{
		pthread_mutex_unlock(&philo->start->mutex.is_death);
		return ;
	}
	if (action == 0)
	{
		printf("\033[32m%lld %d has taken a fork\n\033[0m", gt(*time),
			philo->content);
	}
	else if (action == 1)
		printf("\033[33m%lld %d is eating\n\033[0m", gt(*time), philo->content);
	else if (action == 2)
		printf("\033[36m%lld %d is sleeping\n\033[0m", gt(*time),
			philo->content);
	else if (action == 3)
		printf("\033[95m%lld %d is thinking\n\033[0m", gt(*time),
			philo->content);
	else
		printf("\033[91m%lld %d died\n\033[0m", gt(*time), philo->content);
	pthread_mutex_unlock(&philo->start->mutex.is_death);
}
