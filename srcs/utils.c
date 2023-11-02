/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 09:50:30 by paulabiazot       #+#    #+#             */
/*   Updated: 2023/11/02 09:24:42 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long int	ft_atoi(const char *nptr)
{
	int			signal;
	long int	result;

	signal = 1;
	result = 0;
	while (*nptr == ' ' || (*nptr >= 9 && *nptr <= 13))
		nptr++;
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			signal = signal * -1;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		result = result * 10 + (*nptr - '0');
		nptr++;
	}
	return ((long int)result * signal);
}

int	just_one(char **av)
{
	if (ft_atoi(av[1]) == 1)
	{
		printf("\033[32m%i %d took a fork\n\e[0m", 0, 1);
		usleep(ft_atoi(av[2]) * 1000);
		printf("\033[91m%li %d died\n\e[0m", ft_atoi(av[2]) + 1, 1);
		return (1);
	}
	return (0);
}
