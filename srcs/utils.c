/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulabiazotto <paulabiazotto@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 09:50:30 by paulabiazot       #+#    #+#             */
/*   Updated: 2023/10/27 11:02:35 by paulabiazot      ###   ########.fr       */
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

int	take_fork(t_philo *philo)
{
	if (philo->content % 2 != 0)
	{
		pthread_mutex_lock(&philo->fork);
		printf("philo %d has taken a fork\n", philo->content);
		philo->mutex.is_locked = 1;
		pthread_mutex_lock(&philo->next->fork);
		printf("philo %d has taken a second fork\n", philo->content);
		philo->next->mutex.is_locked = 1;
		return (1);
	}
	else
	{
		pthread_mutex_lock(&philo->next->fork);
		printf("philo %d has taken a fork\n", philo->content);
		philo->mutex.is_locked = 1;
		pthread_mutex_lock(&philo->fork);
		printf("philo %d has taken a second fork\n", philo->content);
		philo->next->mutex.is_locked = 1;
		return (1);
	}
	return (0);
}

void	unlocked_fork(t_philo *philo)
{
	if (philo->content % 2 == 0)
	{
		pthread_mutex_lock(&philo->mutex.forks);
		philo->mutex.is_locked = 0;
		philo->next->mutex.is_locked = 0;
		pthread_mutex_unlock(&philo->mutex.forks);
		pthread_mutex_unlock(&philo->next->fork);
		pthread_mutex_unlock(&philo->fork);
		printf("philo %d has unlock a fork\n", philo->content);
		printf("philo %d has unlock a second fork\n", philo->content);
	}
	else
	{
		pthread_mutex_lock(&philo->mutex.forks);
		philo->mutex.is_locked = 0;
		philo->next->mutex.is_locked = 0;
		pthread_mutex_unlock(&philo->mutex.forks);
		pthread_mutex_unlock(&philo->fork);
		pthread_mutex_unlock(&philo->next->fork);
		printf("philo %d has unlock a second fork\n", philo->content);
		printf("philo %d has unlock a first fork\n", philo->content);
	}
}
