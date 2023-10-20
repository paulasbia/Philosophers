/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulabiazotto <paulabiazotto@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 09:54:04 by paulabiazot       #+#    #+#             */
/*   Updated: 2023/10/20 14:35:16 by paulabiazot      ###   ########.fr       */
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
	pthread_mutex_lock(&philo->fork);
	printf("philo %d has taken a fork\n", philo->content);
	pthread_mutex_lock(&philo->next->fork);
	printf("philo %d has taken a second fork\n", philo->content);
}

void	go_eat(t_philo *philo)
{
	printf("philo %d is eating\n", philo->content);
	pthread_mutex_unlock(&philo->fork);
	printf("philo %d has unlock a fork\n", philo->content);
	pthread_mutex_unlock(&philo->next->fork);
	printf("philo %d has unlock a second fork\n", philo->content);
}

void	*routine(void *arg)
{
	int	dead;
	t_philo	*node;
//	t_table	*first;

	node = (t_philo *)arg;
//	first = node;
	dead = 0;
	while (life(node, &dead))
	{
		printf("entrou\n");
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
