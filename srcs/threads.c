/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 09:54:04 by paulabiazot       #+#    #+#             */
/*   Updated: 2023/11/09 17:21:17 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	go_eat(t_philo *philo, struct timeval *time)
{
	philo->last_eat = gt(philo->start_time);
	philo->status = EAT;
	msg(philo, time, 1);
	philo->times.t_eaten++;
	if (philo->times.t_must_eat)
	{
		if (check_eat(philo) == philo->start->num_philo)
		{
			pthread_mutex_lock(&philo->start->mutex.is_done);
			philo->start->all_done = 1;
			pthread_mutex_unlock(&philo->start->mutex.is_done);
			unlocked_fork(philo);
			return (1);
		}
	}
	while (gt(philo->start_time) - philo->last_eat < philo->times.t_eat)
	{
		if (!(check_life(philo)) || is_dead(philo, time))
		{
			unlocked_fork(philo);
			return (1);
		}
	}
	unlocked_fork(philo);
	return (0);
}

int	go_sleep(t_philo *philo, struct timeval *time)
{
	msg(philo, time, 2);
	philo->status = SLEEP;
	while (gt(philo->start_time) - philo->last_eat < philo->times.t_sleep
		+ philo->times.t_eat)
	{
		if (!(check_life(philo)) || is_dead(philo, time))
			return (1);
	}
	return (0);
}

void	go_think(t_philo *philo, struct timeval *time)
{
	int	sleep;

	sleep = 0;
	msg(philo, time, 3);
	if (gt(philo->start_time) - philo->last_eat < philo->times.t_death)
	{
		sleep = (philo->times.t_death - (gt(philo->start_time)
					- philo->last_eat));
		usleep(1000 * (sleep / 3));
	}
	philo->status = THINK;
}

void	*routine(void *node)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	((t_philo *)node)->start_time = time;
	if (((t_philo *)node)->content % 2 == 0)
		usleep(1000);
	while (1)
	{
		if (!(check_life(node)) || (is_dead(node, &time)))
			break ;
		if (((t_philo *)node)->status == THINK)
		{
			if (take_fork(node, &time) == 0)
				if (go_eat(node, &time))
					break ;
		}
		else if (((t_philo *)node)->status == EAT)
			go_sleep(node, &time);
		else if (((t_philo *)node)->status == SLEEP)
			go_think(node, &time);
	}
	return (NULL);
}

int	start_thread(t_start start, t_philo *table)
{
	pthread_t	*th;
	t_philo		*temp;
	int			i;

	i = 0;
	th = (pthread_t *)malloc(sizeof(pthread_t) * start.num_philo);
	temp = table;
	while (i < start.num_philo)
	{
		if (pthread_create(&th[i], NULL, &routine, (t_philo *)temp) != 0)
			return (error_msg("Failed to create thread"));
		i++;
		temp = temp->next;
	}
	i = 0;
	while (i < start.num_philo)
	{
		if (pthread_join(th[i], NULL) != 0)
			return (error_msg("Failed to join thread!"));
		i++;
	}
	destroy_mutex(&start, table);
	free(th);
	return (0);
}
