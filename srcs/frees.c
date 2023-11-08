/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 16:24:12 by paulabiazot       #+#    #+#             */
/*   Updated: 2023/11/08 15:34:11 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	destroy_mutex(t_start *start, t_philo *new)
{
	pthread_mutex_destroy(&start->mutex.is_death);
	pthread_mutex_destroy(&start->mutex.is_eaten);
	pthread_mutex_destroy(&new->fork);
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
