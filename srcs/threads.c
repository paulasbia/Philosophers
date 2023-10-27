/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulabiazotto <paulabiazotto@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 09:54:04 by paulabiazot       #+#    #+#             */
/*   Updated: 2023/10/27 11:02:28 by paulabiazot      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	is_dead(t_philo *philo, int *died)
{
	if (gt(philo->start_time) - philo->last_eat > philo->times.t_death)
	{
		printf("philo %d morre\n", philo->content);
		pthread_mutex_lock(&philo->mutex.is_death);
		*died = 1;
		pthread_mutex_unlock(&philo->mutex.is_death);
		return (1);
	}
	return (0);
}

int	go_eat(t_philo *philo, int *dead)
{
	philo->last_eat = gt(philo->start_time);
	printf("philo %d is eating\n", philo->content);
	philo->times.t_eaten++;
	if (philo->times.t_must_eat)
		check_eat(philo);
	while (gt(philo->start_time) - philo->last_eat < philo->times.t_eat)
	{
		if (!(check_life(philo, dead)) || is_dead(philo, dead))
			return (1);
	}
	unlocked_fork(philo);
	return (0);
}

int	go_sleep(t_philo *philo, int *died)
{
	printf("philo %d is sleep now......\n", philo->content);
	while (gt(philo->start_time) - philo->last_eat < philo->times.t_sleep
		+ philo->times.t_eat)
	{
		if (!(check_life(philo, died)) || is_dead(philo, died))
			return (1);
	}
	return (0);
}

void	*routine(void *arg)
{
	int						dead;
	t_philo					*node;
	static struct timeval	time;

	node = (t_philo *)arg;
	pthread_mutex_lock(&node->mutex.is_death);
	dead = 0;
	gettimeofday(&time, NULL);
	pthread_mutex_unlock(&node->mutex.is_death);
	node->start_time = time;
	if (node->content % 2 == 0)
		usleep(1000);
	while (1)
	{
		if (!(check_life(node, &dead)) || (is_dead(node, &dead)))
			break ;
		if (!(node->mutex.is_locked) && !(node->next->mutex.is_locked))
			if (take_fork(node))
				if (!(go_eat(node, &dead)))
					if (!(go_sleep(node, &dead)))
						printf("philo %d esta pensando\n", node->content);
	}
	return (NULL);
}

int	start_thread(t_start start)
{
	pthread_t	*th;
	t_philo		*temp;
	int			i;

	i = 0;
	th = (pthread_t *)malloc(sizeof(pthread_t) * start.num_philo);
	temp = start.forks;
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
	destroy_mutex(&start);
	return (0);
}
