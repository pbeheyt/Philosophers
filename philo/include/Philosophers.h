/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 04:41:55 by pbeheyt           #+#    #+#             */
/*   Updated: 2022/10/18 21:50:06 by pbeheyt          ###   ########.fr       */
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

# define PHILO_WAIT 1000
# define WAIT_CUSTOM_SLEEP 1000

enum e_error
{
	GLOBAL_ERROR,
	NB_ARGS_ERROR,
	NB_PHILO_ERROR,
	MIN_TIME_ERROR,
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
	pthread_mutex_t			m_end;
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
	int			m_end;
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
void		*ft_memset(void *s, int c, size_t n);

/*routine.c*/
void		*routine(void *void_arg);

/*solve.c*/
int			solve(t_data *data);

/*utlis.c*/
long long	get_curr_time(void);
void		custom_usleep(t_data *data, long long ms);
int			print(t_data *data, int i, int died, char *msg);

#endif