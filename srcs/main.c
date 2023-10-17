/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulabiazotto <paulabiazotto@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 09:21:31 by paulabiazot       #+#    #+#             */
/*   Updated: 2023/10/17 12:08:24 by paulabiazot      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int ac, char **av)
{
	(void)av;
	if (check_args(ac, av) == 1)
		return (1);
}
