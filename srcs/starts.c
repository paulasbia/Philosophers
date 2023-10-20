/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   starts.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulabiazotto <paulabiazotto@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 11:12:31 by paulabiazot       #+#    #+#             */
/*   Updated: 2023/10/20 14:32:11 by paulabiazot      ###   ########.fr       */
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

t_philo	*create_node(int content)
{
	t_philo	*new;

	new = (t_philo *)malloc(sizeof(t_philo));
	if (new == 0)
		return (NULL);
    pthread_mutex_init(&new->fork, NULL);
    pthread_mutex_init(&new->mutex.is_death, NULL);
    pthread_mutex_init(&new->mutex.is_write, NULL);
	new->content = content;
	new->next = 0;
	return (new);
}

t_philo	*ft_lstlast(t_philo *lst)
{
    t_philo *first;

	if (!lst)
		return (NULL);
    first = lst;
	while (lst->next != first)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back(t_philo **lst, t_philo *new)
{
	t_philo	*last;

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

t_philo	*create_table(int philo)
{
	t_philo	*table;
	t_philo	*temp;
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
	return (table);
}
