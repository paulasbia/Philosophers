/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulabiazotto <paulabiazotto@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 10:31:07 by paulabiazot       #+#    #+#             */
/*   Updated: 2023/10/20 11:14:15 by paulabiazot      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define FIRST_FORK 0
# define SECOND_FORK 1
# define EAT 2
# define SLEEP 3
# define THINK 4
# define DIED 5

typedef struct s_times
{
	int				t_death;
	int				t_sleep;
	int				t_eat;
	int				t_must_eat;
}					t_times;

typedef struct s_table
{
	pthread_mutex_t	fork;
	int				content;
	struct s_table	*next;
}					t_table;

typedef struct s_mutex
{
	pthread_mutex_t		is_death;
	pthread_mutex_t		is_write;
	pthread_mutex_t		forks;
}	t_mutex;

typedef struct s_start
{
	int				num_philo;
	t_times			times;
	t_table			*forks;
	t_mutex			mutex;
}					t_start;

int					check_args(int ac, char **av);
int					error_msg(const char *msg);
int					ft_atoi(const char *nptr);
void				lets_start(t_start *start, char **av, int ac);
t_table				*create_table(int philo);
int					start_thread(t_start start);
void				destroy_mutex(t_start *start);
void				ft_lstclear(t_table **lst);

#endif