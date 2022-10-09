/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 04:41:55 by pbeheyt           #+#    #+#             */
/*   Updated: 2022/10/09 08:36:43 by pbeheyt          ###   ########.fr       */
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
# define WAIT_CHECK_END_LOOP 100

enum e_error
{
	GLOBAL_ERROR,
	NB_ARGS_ERROR,
	NB_PHILO_ERROR,
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
	struct s_philosopher	*phi;
	struct s_check_status	*cs;
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

typedef struct s_check_status
{
	int			m_eat;
	int			m_print;
	int			m_forks;
	int			threads;
}				t_check_status;

/*clear.c*/
void		clear_all(t_data *data);

/*error_handler.c*/
int			error_handler(t_data *data, int error, int clear);

/*init.c*/
int			init(t_data *data, int ac, char **av);

/*libft.c*/
size_t		ft_strlen(const char *str);
int			ft_atoi(const char *str, int *error);
void		ft_putstr_fd(char *s, int fd);

/*routine.c*/
void		*routine(void *void_arg);

/*solve.c*/
int			solve(t_data *data);

/*utlis.c*/
long long	get_curr_time(void);
void		custom_usleep(t_data *data, int ms);
void		print(t_data *data, int i, char *msg);

#endif