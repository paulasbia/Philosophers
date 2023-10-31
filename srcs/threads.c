/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulabiazotto <paulabiazotto@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 09:54:04 by paulabiazot       #+#    #+#             */
/*   Updated: 2023/10/31 10:17:14 by paulabiazot      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	is_dead(t_philo *philo, struct timeval *time)
{
	if (gt(philo->start_time) - philo->last_eat > philo->times.t_death)
	{
		pthread_mutex_lock(&philo->start->mutex.is_death);
		if (philo->start->death == 0)
			printf("%lld philo %d died\n", gt(*time), philo->content);
		philo->start->death = 1;
		pthread_mutex_unlock(&philo->start->mutex.is_death);
		return (1);
	}
	return (0);
}

int	go_eat(t_philo *philo, struct timeval *time)
{
	philo->last_eat = gt(philo->start_time);
	printf("%lld philo %d is eating\n", gt(*time), philo->content);
	philo->times.t_eaten++;
	if (philo->times.t_must_eat)
		check_eat(philo);
	while (gt(philo->start_time) - philo->last_eat < philo->times.t_eat)
	{
		if (!(check_life(philo)) || is_dead(philo, time))
		{
			unlocked_fork(philo, time);
			return (1);
		}
	}
	unlocked_fork(philo, time);
	return (0);
}

int	go_sleep(t_philo *philo, struct timeval *time)
{
	printf("%lld philo %d is sleeping\n", gt(*time), philo->content);
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
		if (!(node->mutex.is_locked) && !(node->next->mutex.is_locked)
			&& !is_dead(node, &time))
			if (take_fork(node, &time) && !is_dead(node, &time))
				if (!(go_eat(node, &time)) && !is_dead(node, &time))
					if (!(go_sleep(node, &time)) && !is_dead(node, &time))
						printf("%lld philo %d is thinking\n", gt(time),
							node->content);
	}
	printf("saiu philo %d\n", node->content);
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
			error_msg("Failed to create thread");
		i++;
		temp = temp->next;
	}
	i = 0;
	while (i < start.num_philo)
	{
		if (pthread_join(th[i], NULL) != 0)
			error_msg("Failed to join thread!");
		i++;
	}
	printf("se morreu, desaloque\n");
	destroy_mutex(&start);
	return (0);
}
