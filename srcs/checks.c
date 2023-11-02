/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulabiazotto <paulabiazotto@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:21:06 by paulabiazot       #+#    #+#             */
/*   Updated: 2023/11/02 14:11:27 by paulabiazot      ###   ########.fr       */
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

int	check_args2(int ac, char **av)
{
	if (ft_atoi(av[1]) > 1000 || ft_atoi(av[2]) > MAX_INT
		|| ft_atoi(av[3]) > MAX_INT || ft_atoi(av[4]) > MAX_INT
		|| ft_atoi(av[2]) < 0 || ft_atoi(av[3]) < 0 || ft_atoi(av[4]) < 0)
		return (error_msg("Argument TOO BIG!\n"));
	if (ac == 6 && (ft_atoi(av[5]) > MAX_INT || ft_atoi(av[5]) < 1))
		return (error_msg("Argument invalid or TOO BIG!\n"));
	return (0);
}

int	check_args(int ac, char **av)
{
	int	i;

	if (ac > 6 || ac < 5)
		return (error_msg("Number of arguments is wrong!\n"));
	i = 1;
	while (i < ac)
	{
		if (is_number(av[i]) == 1)
			return (error_msg("rgument is invalid!\n"));
		i++;
	}
	if (check_args2(ac, av))
		return (1);
	if (just_one(av))
		return (1);
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
