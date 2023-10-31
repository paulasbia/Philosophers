/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulabiazotto <paulabiazotto@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 10:31:07 by paulabiazot       #+#    #+#             */
/*   Updated: 2023/10/31 16:10:37 by paulabiazot      ###   ########.fr       */
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
	int				t_eaten;
	int				t_eating;
}					t_times;

typedef struct s_mutex
{
	pthread_mutex_t	is_death;
	int				is_locked;
	pthread_mutex_t	is_write;
	pthread_mutex_t	is_eating;
	pthread_mutex_t	forks;
}					t_mutex;

typedef struct s_start
{
	int				num_philo;
	int				death;
	t_mutex			mutex;
}					t_start;

typedef struct s_philo
{
	int				num_philo;
	struct timeval	start_time;
	long long int	last_eat;
	pthread_mutex_t	fork;
	t_times			times;
	t_mutex			mutex;
	int				content;
	struct s_philo	*next;
	t_start			*start;
}					t_philo;

int					check_args(int ac, char **av);
int					error_msg(const char *msg);
void				msg(t_philo *philo, struct timeval *time, int action);
int					ft_atoi(const char *nptr);
void				lets_start(t_start *start, char **av, int ac);
t_philo				*create_table(t_start *start, char **av, int ac);
long long int		gt(struct timeval start);
int					check_life(t_philo *philo);
int					take_fork(t_philo *philo, struct timeval *time);
void				unlocked_fork(t_philo *philo, struct timeval *time);
int					check_eat(t_philo *philo);
int					start_thread(t_start start, t_philo *table);
int					is_dead(t_philo *philo, struct timeval *time);
void				destroy_mutex(t_start *start);
void				ft_lstclear(t_philo **lst);

#endif