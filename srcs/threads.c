/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulabiazotto <paulabiazotto@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 09:54:04 by paulabiazot       #+#    #+#             */
/*   Updated: 2023/10/23 13:06:44 by paulabiazot      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	life(t_philo *philo, int *dead)
{
	pthread_mutex_lock(&philo->mutex.is_death);
	if (*dead == 1)
	{
		pthread_mutex_unlock(&philo->mutex.is_death);
		return (0);
	}
	pthread_mutex_unlock(&philo->mutex.is_death);
	return (1);
}

void	take_fork(t_philo *philo)
{
	if (philo->content % 2 != 0)
	{
		pthread_mutex_lock(&philo->fork);
		printf("philo %d has taken a fork\n", philo->content);
		philo->mutex.is_locked = 1;
		pthread_mutex_lock(&philo->next->fork);
		printf("philo %d has taken a second fork\n", philo->content);
		philo->next->mutex.is_locked = 1;
	}
	else
	{
		pthread_mutex_lock(&philo->next->fork);
		printf("philo %d has taken a fork\n", philo->content);
		philo->mutex.is_locked = 1;
		pthread_mutex_lock(&philo->fork);
		printf("philo %d has taken a second fork\n", philo->content);
		philo->next->mutex.is_locked = 1;
	}
}

void	go_eat(t_philo *philo)
{
	printf("philo %d is eating\n", philo->content);
	pthread_mutex_unlock(&philo->fork);
	printf("philo %d has unlock a fork\n", philo->content);
	pthread_mutex_unlock(&philo->next->fork);
	printf("philo %d has unlock a second fork\n", philo->content);
	philo->mutex.is_locked = 0;
	philo->next->mutex.is_locked = 0;
}

void	*routine(void *arg)
{
	int		dead;
	t_philo	*node;

	node = (t_philo *)arg;
	dead = 0;
	while (life(node, &dead))
	{
		if (!(node->mutex.is_locked) && !(node->next->mutex.is_locked))
			take_fork(node);
		go_eat(node);
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
