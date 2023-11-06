/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-souz <pde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 16:24:12 by paulabiazot       #+#    #+#             */
/*   Updated: 2023/11/06 11:06:49 by pde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	destroy_mutex(t_start *start, t_philo *new)
{
	pthread_mutex_destroy(&start->mutex.is_death);
	pthread_mutex_init(&new->fork, NULL);
	pthread_mutex_init(&new->mutex.is_write, NULL);
	pthread_mutex_init(&new->mutex.forks, NULL);
}

void	ft_lstclear(t_philo **lst)
{
	t_philo	*temp;
	t_philo	*first;

	first = *lst;
	while (*lst != 0)
	{
		temp = (*lst)->next;
		free(*lst);
		*lst = temp;
		if (*lst == first)
			break ;
	}
	*lst = NULL;
}
