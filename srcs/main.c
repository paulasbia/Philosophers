/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 09:21:31 by paulabiazot       #+#    #+#             */
/*   Updated: 2023/11/04 11:13:00 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int ac, char **av)
{
	t_start	start;
	t_philo	*list;

	if (check_args(ac, av))
		return (1);
	lets_start(&start, av, ac);
	list = create_table(&start, av, ac);
	start_thread(start, list);
	ft_lstclear(&list);
}
