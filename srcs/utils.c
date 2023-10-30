/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulabiazotto <paulabiazotto@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 09:50:30 by paulabiazot       #+#    #+#             */
/*   Updated: 2023/10/30 17:24:24 by paulabiazot      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_atoi(const char *nptr)
{
	int	signal;
	int	result;

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
	return (result * signal);
}

int	take_fork(t_philo *philo, struct timeval *time)
{
	printf("%lld philo %d vai pegar\n", gt(*time), philo->content);
	if (philo->content % 2 != 0)
	{
		while (philo->mutex.is_locked)
		{
			usleep(50);
			if (is_dead(philo, time))
				return (1);	
		}
		pthread_mutex_lock(&philo->fork);
		printf("%lld philo %d has taken a fork\n", gt(*time), philo->content);
		philo->mutex.is_locked = 1;
		while (philo->next->mutex.is_locked)
		{
			usleep(50);
			if (is_dead(philo, time))
			{
				unlocked_fork(philo, time);
				return (1);	
			}
		}
		pthread_mutex_lock(&philo->next->fork);
		printf("%lld philo %d has taken a fork\n", gt(*time), philo->content);
		philo->next->mutex.is_locked = 1;
		return (1);
	}
	else
	{
		while (philo->next->mutex.is_locked)
		{
			usleep(50);
			if (is_dead(philo, time))
				return (1);	
		}
		pthread_mutex_lock(&philo->next->fork);
		printf("%lld philo %d has taken a fork\n", gt(*time), philo->content);
		philo->mutex.is_locked = 1;
		while (philo->mutex.is_locked)
		{
			usleep(50);
			if (is_dead(philo, time))
			{
				unlocked_fork(philo->next, time);
				return (1);
			}
		}
		pthread_mutex_lock(&philo->fork);
		printf("%lld philo %d has taken a fork\n", gt(*time), philo->content);
		philo->next->mutex.is_locked = 1;
		return (1);
	}
	return (0);
}

void	unlocked_fork(t_philo *philo, struct timeval *time)
{
	if (philo->content % 2 == 0)
	{
		pthread_mutex_lock(&philo->mutex.forks);
		philo->mutex.is_locked = 0;
		philo->next->mutex.is_locked = 0;
		pthread_mutex_unlock(&philo->mutex.forks);
		pthread_mutex_unlock(&philo->next->fork);
		pthread_mutex_unlock(&philo->fork);
		printf("%lld philo %d has unlock a fork\n", gt(*time), philo->content);
		printf("%lld philo %d has unlock a second fork\n", gt(*time), philo->content);
	}
	else
	{
		pthread_mutex_lock(&philo->mutex.forks);
		philo->mutex.is_locked = 0;
		philo->next->mutex.is_locked = 0;
		pthread_mutex_unlock(&philo->mutex.forks);
		pthread_mutex_unlock(&philo->fork);
		pthread_mutex_unlock(&philo->next->fork);
		printf("%lld philo %d has unlock a second fork\n", gt(*time), philo->content);
		printf("%lld philo %d has unlock a first fork\n", gt(*time), philo->content);
	}
}
