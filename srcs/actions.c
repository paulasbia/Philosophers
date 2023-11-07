/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 09:25:18 by paulabiazot       #+#    #+#             */
/*   Updated: 2023/11/07 11:19:26 by paula            ###   ########.fr       */
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

t_grab_fork try_grab_this_fork(t_philo *philo){
	t_grab_fork grabit;
	
	pthread_mutex_lock(&philo->fork);
	if (philo->mutex.is_locked){
		grabit = IT_DIDNT_WORK;	
	}else{
		philo->mutex.is_locked = 1;
		grabit = IT_WORKED;
	}
	pthread_mutex_unlock(&philo->fork);
	return grabit;
}

int	take_fork(t_philo *philo, struct timeval *time)
{
	t_philo* first;
	t_philo* second;
	if (philo->content % 2 != 0)
	{
		first = philo;
		second = philo->next;
	}
	else
	{
		first = philo->next;
		second = philo;
	}
	while(try_grab_this_fork(first) != IT_WORKED){
		if (is_dead(first, time))
			return (1);
	}
	msg(philo, time, 0);
		
	while(try_grab_this_fork(second->next) != IT_WORKED){
		if (is_dead(second, time))
			return (1);
	}
	msg(philo, time, 0);
	return (0);
}


void release_this_fork(t_philo *philo){
	pthread_mutex_lock(&philo->fork);
	philo->mutex.is_locked = 0;
	pthread_mutex_unlock(&philo->fork);
}

void	unlocked_fork(t_philo *philo)
{
	if (philo->content % 2 == 0)
	{
		release_this_fork(philo);
		release_this_fork(philo->next);
	}
	else
	{
		release_this_fork(philo->next);
		release_this_fork(philo);
	}
}
