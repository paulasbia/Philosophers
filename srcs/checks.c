/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulabiazotto <paulabiazotto@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:21:06 by paulabiazot       #+#    #+#             */
/*   Updated: 2023/10/17 11:59:38 by paulabiazot      ###   ########.fr       */
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

int check_args(int ac , char **av)
{
    int i;
    (void)av;
    if (ac > 6 || ac < 5)
        error_msg("Number of arguments is wrong!\n");
    i = 1;
    while (i < ac)
	{
		if (is_number(av[i]) == 1)
			error_msg("Argument is invalid!\n");
		i++;
	}
    return (0);
}