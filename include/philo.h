/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulabiazotto <paulabiazotto@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 10:31:07 by paulabiazot       #+#    #+#             */
/*   Updated: 2023/10/18 11:13:18 by paulabiazot      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_times
{
	int		t_death;
	int		t_sleep;
	int		t_eat;
	int		t_must_eat;
}			t_times;

typedef struct s_start
{
	int		num_philo;
	t_times	times;
}			t_start;

int			check_args(int ac, char **av);
int			error_msg(const char *msg);
int			ft_atoi(const char *nptr);
void		lets_start(t_start *start, char **av);
int			start_thread(int num_philo);

#endif