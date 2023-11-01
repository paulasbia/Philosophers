/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulabiazotto <paulabiazotto@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 09:25:18 by paulabiazot       #+#    #+#             */
/*   Updated: 2023/11/01 09:25:48 by paulabiazot      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	msg(t_philo *philo, struct timeval *time, int action)
{
	pthread_mutex_lock(&philo->mutex.is_write);
	if (!check_life(philo))
	{
		pthread_mutex_unlock(&philo->mutex.is_write);
		return ;
	}
	if (action == 0)
	{
		printf("%lld philo %d has taken a fork\n", gt(*time), philo->content);
		printf("%lld philo %d has taken a fork\n", gt(*time), philo->content);
	}
	else if (action == 1)
		printf("%lld philo %d is eating\n", gt(*time), philo->content);
	else if (action == 2)
		printf("%lld philo %d is sleeping\n", gt(*time), philo->content);
	else if (action == 3)
		printf("%lld philo %d is thinking\n", gt(*time), philo->content);
	else
		printf("%lld philo %d died\n", gt(*time), philo->content);
	pthread_mutex_unlock(&philo->mutex.is_write);
}

int	go_check(t_philo *philo, struct timeval *time)
{
	while (philo->mutex.is_locked || philo->next->mutex.is_locked)
	{
		usleep(50);
		if (is_dead(philo, time))
			return (1);
	}
	return (0);
}

int	take_fork(t_philo *philo, struct timeval *time)
{
	if (philo->content % 2 != 0)
	{
		if (go_check(philo, time))
			return (1);
		pthread_mutex_lock(&philo->fork);
		pthread_mutex_lock(&philo->next->fork);
		philo->next->mutex.is_locked = 1;
		philo->mutex.is_locked = 1;
		msg(philo, time, 0);
		return (1);
	}
	else
	{
		if (go_check(philo, time))
			return (1);
		pthread_mutex_lock(&philo->next->fork);
		pthread_mutex_lock(&philo->fork);
		philo->next->mutex.is_locked = 1;
		philo->mutex.is_locked = 1;
		msg(philo, time, 0);
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
		printf("%lld philo %d has unlock a second fork\n", gt(*time),
			philo->content);
	}
	else
	{
		pthread_mutex_lock(&philo->mutex.forks);
		philo->mutex.is_locked = 0;
		philo->next->mutex.is_locked = 0;
		pthread_mutex_unlock(&philo->mutex.forks);
		pthread_mutex_unlock(&philo->fork);
		pthread_mutex_unlock(&philo->next->fork);
		printf("%lld philo %d has unlock a second fork\n", gt(*time),
			philo->content);
		printf("%lld philo %d has unlock a first fork\n", gt(*time),
			philo->content);
	}
}
