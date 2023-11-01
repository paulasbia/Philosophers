/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulabiazotto <paulabiazotto@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 09:25:18 by paulabiazot       #+#    #+#             */
/*   Updated: 2023/11/01 15:12:30 by paulabiazot      ###   ########.fr       */
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
		printf("\033[32m%lld philo %d has taken a fork\n\e[0m", gt(*time),
			philo->content);
		printf("\033[32m%lld philo %d has taken a fork\n\e[0m", gt(*time),
			philo->content);
	}
	else if (action == 1)
		printf("\033[33m%lld philo %d is eating\n\e[0m", gt(*time),
			philo->content);
	else if (action == 2)
		printf("\033[36m%lld philo %d is sleeping\n\e[0m", gt(*time),
			philo->content);
	else if (action == 3)
		printf("\033[95m%lld philo %d is thinking\n\e[0m", gt(*time),
			philo->content);
	else
		printf("\033[91m%lld philo %d died\n\e[0m", gt(*time), philo->content);
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
	}
	else
	{
		pthread_mutex_lock(&philo->mutex.forks);
		philo->mutex.is_locked = 0;
		philo->next->mutex.is_locked = 0;
		pthread_mutex_unlock(&philo->mutex.forks);
		pthread_mutex_unlock(&philo->fork);
		pthread_mutex_unlock(&philo->next->fork);
	}
}
