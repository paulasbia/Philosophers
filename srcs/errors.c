/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulabiazotto <paulabiazotto@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:26:53 by paulabiazot       #+#    #+#             */
/*   Updated: 2023/10/17 11:57:44 by paulabiazot      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	error_msg(const char *msg)
{
	printf("\033[31mERROR - %s\e[0m", msg);
    return (1);
}
