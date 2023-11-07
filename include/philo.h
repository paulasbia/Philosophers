/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 10:31:07 by paulabiazot       #+#    #+#             */
/*   Updated: 2023/11/07 11:00:07 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define MAX_INT 2147483647

# define FIRST_FORK 0
# define SECOND_FORK 1
# define EAT 2
# define SLEEP 3
# define THINK 4
# define DIED 5

typedef enum grab_fork_
{
	IT_WORKED,
	IT_DIDNT_WORK
}					t_grab_fork;

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

int					just_one(char **av);
int					check_args(int ac, char **av);
int					error_msg(const char *msg);
void				msg(t_philo *philo, struct timeval *time, int action);
long int			ft_atoi(const char *nptr);
void				lets_start(t_start *start, char **av, int ac);
t_philo				*create_table(t_start *start, char **av, int ac);
long long int		gt(struct timeval start);
int					check_life(t_philo *philo);
int					take_fork(t_philo *philo, struct timeval *time);
void				unlocked_fork(t_philo *philo);
int					check_eat(t_philo *philo);
int					start_thread(t_start start, t_philo *table);
int					is_dead(t_philo *philo, struct timeval *time);
void				destroy_mutex(t_start *start, t_philo *new);
void				ft_lstclear(t_philo **lst);

#endif