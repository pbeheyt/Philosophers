/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 04:41:55 by pbeheyt           #+#    #+#             */
/*   Updated: 2022/09/29 12:38:01 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>

# define PHILO_WAIT_TO_START 15000
# define WAIT_CHECK_END_LOOP 150

enum e_error
{
	GLOBAL_ERROR,
	NB_ARGS_ERROR,
	ARGS_ERROR,
	MUTEX_ERROR,
	THREAD_ERROR,
	ALLOC_ERROR,
};

struct	s_philosopher;

typedef struct s_data
{
	int						error;
	int						nb_phi;
	int						time_to_die;
	int						time_to_eat;
	int						time_to_sleep;
	int						nb_meals;
	int						has_died;
	int						all_ate;
	long long				launch_time;
	pthread_mutex_t			m_eat;
	pthread_mutex_t			*m_forks;
	pthread_mutex_t			m_print;
	pthread_mutex_t			m_check_end;
	struct s_philosopher	*phi;
}				t_data;

typedef struct s_philosopher
{
	int			i;
	int			nb_meals;
	int			lfork_i;
	int			rfork_i;
	long long	time_last_meal;
	int			done_eating;
	pthread_t	thread;
	t_data		*data;
}				t_philosopher;

/*clear.c*/
void		clear_all(t_data *data);

/*error_handler.c*/
int			error_handler(t_data *data, int error);

/*utlis.c*/
int			ft_atoi(const char *str, int *error);
void		ft_putstr_fd(char *s, int fd);
long long	get_current_time(void);
void		print(t_data *data, int i, char *msg);

/*init.c*/
int			init(t_data *data, int ac, char **av);

/*routine.c*/
void		*routine(void *void_arg);

/*solve.c*/
int			solve(t_data *data);

#endif