/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulabiazotto <paulabiazotto@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 16:24:12 by paulabiazot       #+#    #+#             */
/*   Updated: 2023/10/18 18:09:51 by paulabiazot      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	destroy_mutex(t_start *start)
{
	pthread_mutex_destroy(&start->mutex.is_death);
	pthread_mutex_destroy(&start->mutex.is_write);
	pthread_mutex_destroy(&start->mutex.forks);
}

void	ft_lstclear(t_table **lst)
{
	t_table	*temp;
    t_table *first;

    first = *lst;
	while (*lst != 0)
	{
		temp = (*lst)->next;
        printf("liberou\n");
		free(*lst);
		*lst = temp;
        if (*lst == first)
            break;
	}
	*lst = NULL;
}
