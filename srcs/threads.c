/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 09:54:04 by paulabiazot       #+#    #+#             */
/*   Updated: 2023/11/07 18:31:16 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	is_dead(t_philo *philo, struct timeval *time)
{
	int i_died_first = 1;
	if (gt(philo->start_time) - philo->last_eat > philo->times.t_death)
	{
		pthread_mutex_lock(&philo->start->mutex.is_death);
		if (philo->start->death == 0)
		{
			philo->start->death = philo->content;	
		}else{
			i_died_first = 0;	
		}
		pthread_mutex_unlock(&philo->start->mutex.is_death);
		if(i_died_first)
			msg(philo, time, 4);
		return (1);
	}
	return (0);
}

int	go_eat(t_philo *philo, struct timeval *time)
{
	philo->last_eat = gt(philo->start_time);
	philo->status = EAT;
	msg(philo, time, 1);
	while (gt(philo->start_time) - philo->last_eat < philo->times.t_eat)
	{
		if (!(check_life(philo)) || is_dead(philo, time))
		{
			unlocked_fork(philo);
			return (1);
		}
	}
	unlocked_fork(philo);
	philo->times.t_eaten++;
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

void	*routine(void *arg)
{
	t_philo			*node;
	struct timeval	time;

	node = (t_philo *)arg;
	gettimeofday(&time, NULL);
	node->start_time = time;
	if (node->content % 2 == 0)
		usleep(1000);
	while (1)
	{
		if (!(check_life(node)) || (is_dead(node, &time)))
			break ;
		if (node->status == THINK)
		{
			if(take_fork(node, &time) == 0)
				go_eat(node, &time);
			if (check_eat(node))
				break ;
		}
		else if (node->status == EAT)
			go_sleep(node, &time);
		else if (node->status == SLEEP)
		{
			node->status = THINK;
			msg(node, &time, 3);
		}
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
