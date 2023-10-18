/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   starts.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulabiazotto <paulabiazotto@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 11:12:31 by paulabiazot       #+#    #+#             */
/*   Updated: 2023/10/18 18:42:42 by paulabiazot      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	lets_start(t_start *start, char **av, int ac)
{
	start->num_philo = ft_atoi(av[1]);
	start->times.t_death = ft_atoi(av[2]);
	start->times.t_eat = ft_atoi(av[3]);
	start->times.t_sleep = ft_atoi(av[4]);
	if (ac == 6)
		start->times.t_must_eat = ft_atoi(av[5]);
	pthread_mutex_init(&start->mutex.is_death, NULL);
	pthread_mutex_init(&start->mutex.is_write, NULL);
	pthread_mutex_init(&start->mutex.forks, NULL);
}

t_table	*create_node(int content)
{
	t_table	*new;
//    t_mutex *fork;

	new = (t_table *)malloc(sizeof(t_table));
//    fork = (t_mutex *)malloc(sizeof(t_mutex));
	if (new == 0)
		return (NULL);
   // new->fork_mutex = fork;
	new->content = content;
	new->next = 0;
	return (new);
}

t_table	*ft_lstlast(t_table *lst)
{
    t_table *first;

	if (!lst)
		return (NULL);
    first = lst;
	while (lst->next != first)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back(t_table **lst, t_table *new)
{
	t_table	*last;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
        new->next = new;
		return ;
	}
	last = ft_lstlast(*lst);
    new->next = last->next;
	last->next = new;
}

t_table	*create_table(int philo)
{
	t_table	*table;
	t_table	*temp;
	int		i;

	table = NULL;
	i = 1;
	while (i <= philo)
	{
		temp = create_node(i);
		ft_lstadd_back(&table, temp);
		printf("nó %d\n", i);
		i++;
	}
	ft_lstclear(&table);
	return (table);
}
