/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-souz <pde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 09:25:18 by paulabiazot       #+#    #+#             */
/*   Updated: 2023/11/06 15:26:34 by pde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	msg(t_philo *philo, struct timeval *time, int action)
{
	pthread_mutex_lock(&philo->start->mutex.is_write);
	if (!check_life(philo))
	{
		pthread_mutex_unlock(&philo->start->mutex.is_write);
		return ;
	}
	if (action == 0)
	{
		printf("\033[32m%lld %d has taken a fork\n\033[0m", gt(*time),
			philo->content);
	}
	else if (action == 1)
		printf("\033[33m%lld %d is eating\n\033[0m", gt(*time),
			philo->content);
	else if (action == 2)
		printf("\033[36m%lld %d is sleeping\n\033[0m", gt(*time),
			philo->content);
	else if (action == 3)
		printf("\033[95m%lld %d is thinking\n\033[0m", gt(*time),
			philo->content);
	else
		printf("\033[91m%lld %d died\n\033[0m", gt(*time), philo->content);
	pthread_mutex_unlock(&philo->start->mutex.is_write);
}

int	go_check(t_philo *philo, struct timeval *time)
{
	while (philo->mutex.is_locked || philo->next->mutex.is_locked)
	{
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
		philo->mutex.is_locked = 1;
		msg(philo, time, 0);
		pthread_mutex_lock(&philo->next->fork);
		philo->next->mutex.is_locked = 1;
		msg(philo, time, 0);
	}
	else
	{
		if (go_check(philo, time))
			return (1);
		pthread_mutex_lock(&philo->next->fork);
		philo->next->mutex.is_locked = 1;
		msg(philo, time, 0);
		pthread_mutex_lock(&philo->fork);
		philo->mutex.is_locked = 1;
		msg(philo, time, 0);
	}
	return (0);
}

void	unlocked_fork(t_philo *philo)
{
	if (philo->content % 2 == 0)
	{
		pthread_mutex_unlock(&philo->next->fork);
		pthread_mutex_unlock(&philo->fork);
		philo->mutex.is_locked = 0;
		philo->next->mutex.is_locked = 0;
	}
	else
	{
		pthread_mutex_unlock(&philo->fork);
		pthread_mutex_unlock(&philo->next->fork);
		philo->mutex.is_locked = 0;
		philo->next->mutex.is_locked = 0;
	}
}
