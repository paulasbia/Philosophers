/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   starts.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulabiazotto <paulabiazotto@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 11:12:31 by paulabiazot       #+#    #+#             */
/*   Updated: 2023/10/18 15:21:19 by paulabiazot      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	lets_start(t_start *start, char **av)
{
	start->num_philo = ft_atoi(av[1]);
	printf("philo %d\n", start->num_philo);
	start->times.t_death = ft_atoi(av[2]);
	start->times.t_eat = ft_atoi(av[3]);
	start->times.t_sleep = ft_atoi(av[4]);
	printf("death %d eat %d sleep %d\n", start->times.t_death,
		start->times.t_eat, start->times.t_sleep);
}

t_table	*create_node(int content)
{
	t_table	*new;

	new = (t_table *)malloc(sizeof(t_table));
	if (new == 0)
		return (NULL);
	new->content = content;
	new->next = 0;
	return (new);
}

t_table	*ft_lstlast(t_table *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back(t_table **lst, t_table *new)
{
	t_table	*temp;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	temp = ft_lstlast(*lst);
	temp->next = new;
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
		i++;
	}
	return (table);
}
