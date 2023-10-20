/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulabiazotto <paulabiazotto@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 09:54:04 by paulabiazot       #+#    #+#             */
/*   Updated: 2023/10/20 09:48:13 by paulabiazot      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	take_fork(t_table *philo)
{
	pthread_mutex_lock(&philo->mutex);
	printf("philo %d has taken a fork\n", philo->content);
	pthread_mutex_lock(&philo->next->mutex);
	printf("philo %d has taken a second fork\n", philo->content);
}

void	go_eat(t_table *philo)
{
	printf("philo %d is eating\n", philo->content);
	pthread_mutex_unlock(&philo->mutex);
	printf("philo %d has unlock a fork\n", philo->content);
	pthread_mutex_unlock(&philo->next->mutex);
	printf("philo %d has unlock a second fork\n", philo->content);
}

void	*routine(void *arg)
{
//	pthread_mutex_t	*my_fork;
//	pthread_mutex_t	*next_philo_fork;
	int	i;
	t_table	*node;
//	t_table	*first;

	node = (t_table *)arg;
//	my_fork = &node->mutex;
//	next_philo_fork = &node->next->mutex;
//	first = node;
	i = 0;
	while (i < 1)
	{
		take_fork(node);
		go_eat(node);
		printf("philo %d esta pensando\n", node->content);
		i++;
	}
	return (NULL);
}

int	start_thread(t_start start)
{
	pthread_t	*th;
	t_table		*temp;
	int			i;

	i = 0;
	th = (pthread_t *)malloc(sizeof(pthread_t) * start.num_philo);
	temp = start.forks;
	while (i < start.num_philo)
	{
		if (pthread_create(&th[i], NULL, &routine, (t_table *)temp) != 0)
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
