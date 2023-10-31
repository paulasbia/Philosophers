/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulabiazotto <paulabiazotto@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:21:06 by paulabiazot       #+#    #+#             */
/*   Updated: 2023/10/31 11:03:18 by paulabiazot      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	is_number(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int	check_args(int ac, char **av)
{
	int	i;

	if (ac > 6 || ac < 5)
	{
		error_msg("Number of arguments is wrong!\n");
		return (1);
	}
	i = 1;
	while (i < ac)
	{
		if (is_number(av[i]) == 1)
		{
			error_msg("Argument is invalid!\n");
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_life(t_philo *philo)
{
	pthread_mutex_lock(&philo->start->mutex.is_death);
	if (philo->start->death == 1)
	{
		pthread_mutex_unlock(&philo->start->mutex.is_death);
		return (0);
	}
	pthread_mutex_unlock(&philo->start->mutex.is_death);
	return (1);
}

int	check_eat(t_philo *philo)
{
	if ((philo->times.t_must_eat)
		&& (philo->times.t_must_eat == philo->times.t_eaten))
		return (1);
	return (0);
}
