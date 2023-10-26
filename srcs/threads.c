/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulabiazotto <paulabiazotto@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 09:54:04 by paulabiazot       #+#    #+#             */
/*   Updated: 2023/10/26 10:03:38 by paulabiazot      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	check_life(t_philo *philo, int *dead)
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

int	is_dead(t_philo *philo, int *died)
{
	printf("start time, last eat %lld e t_death %d\n", philo->last_eat,
		philo->times.t_death);
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

int	take_fork(t_philo *philo)
{
	if (philo->content % 2 != 0)
	{
		pthread_mutex_lock(&philo->fork);
		printf("philo %d has taken a fork\n", philo->content);
		philo->mutex.is_locked = 1;
		pthread_mutex_lock(&philo->next->fork);
		printf("philo %d has taken a second fork\n", philo->content);
		philo->next->mutex.is_locked = 1;
		return (1);
	}
	else
	{
		pthread_mutex_lock(&philo->next->fork);
		printf("philo %d has taken a fork\n", philo->content);
		philo->mutex.is_locked = 1;
		pthread_mutex_lock(&philo->fork);
		printf("philo %d has taken a second fork\n", philo->content);
		philo->next->mutex.is_locked = 1;
		return (1);
	}
	return (0);
}

int	go_eat(t_philo *philo, int *dead)
{
	(void)dead;
	philo->last_eat = gt(philo->start_time);
	printf("philo %d is eating\n", philo->content);
	/*while (gt(philo->start_time) - philo->last_eat < philo->times.t_eat)
	{
		if (!(check_life(philo, dead)) || is_dead(philo, dead))
			return (1);
	}*/
	pthread_mutex_unlock(&philo->next->fork);
	printf("philo %d has unlock a fork\n", philo->content);
	philo->mutex.is_locked = 0;
	pthread_mutex_unlock(&philo->fork);
	printf("philo %d has unlock a second fork\n", philo->content);
	philo->next->mutex.is_locked = 0;
	return(0);
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
	while (check_life(node, &dead) || !(is_dead(node, &dead)))
	{
		printf("dead eh %d\n\n", dead);
		if (!(node->mutex.is_locked) && !(node->next->mutex.is_locked))
			if (take_fork(node))
				go_eat(node, &dead);
		printf("philo %d esta pensando\n", node->content);
	}
	printf("dead eh %d\n\n", dead);
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
