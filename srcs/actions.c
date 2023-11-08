/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 09:25:18 by paulabiazot       #+#    #+#             */
/*   Updated: 2023/11/08 16:37:05 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	is_dead(t_philo *philo, struct timeval *time)
{
	int	i_died_first;

	i_died_first = 1;
	if (gt(philo->start_time) - philo->last_eat > philo->times.t_death)
	{
		pthread_mutex_lock(&philo->start->mutex.is_death);
		if (philo->start->death == 0)
		{
			philo->start->death = philo->content;
		}
		else
		{
			i_died_first = 0;
		}
		pthread_mutex_unlock(&philo->start->mutex.is_death);
		if (i_died_first)
			msg(philo, time, 4);
		return (1);
	}
	return (0);
}

t_grab_fork	try_grab_this_fork(t_philo *philo)
{
	t_grab_fork	grabit;

	pthread_mutex_lock(&philo->fork);
	if (philo->mutex.is_locked)
	{
		grabit = IT_DIDNT_WORK;
	}
	else
	{
		philo->mutex.is_locked = 1;
		grabit = IT_WORKED;
	}
	pthread_mutex_unlock(&philo->fork);
	return (grabit);
}

int	take_fork(t_philo *philo, struct timeval *time)
{
	t_philo	*first;
	t_philo	*second;

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
	while (try_grab_this_fork(first) != IT_WORKED)
		if (is_dead(philo, time))
			return (1);
	while (try_grab_this_fork(second) != IT_WORKED)
		if (is_dead(philo, time))
			return (release_this_fork(first));
	msg(philo, time, 0);
	msg(philo, time, 0);
	return (0);
}

int	release_this_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork);
	philo->mutex.is_locked = 0;
	pthread_mutex_unlock(&philo->fork);
	return (1);
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
