/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   starts.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulabiazotto <paulabiazotto@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 11:12:31 by paulabiazot       #+#    #+#             */
/*   Updated: 2023/10/18 11:19:17 by paulabiazot      ###   ########.fr       */
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
