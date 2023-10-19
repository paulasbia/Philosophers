/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulabiazotto <paulabiazotto@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 09:54:04 by paulabiazot       #+#    #+#             */
/*   Updated: 2023/10/19 10:33:43 by paulabiazot      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*routine(void *arg)
{
	int	i;
	t_table	*node;
	pthread_mutex_t	*my_fork;
	pthread_mutex_t	*next_philo_fork;

	node = (t_table *)arg;
	next_philo_fork = &node->next->mutex;
	my_fork = &node->mutex;
	i = 0;
	while (i < 2)
	{
		printf("passou %d thread %d\n", i, node->content);
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
