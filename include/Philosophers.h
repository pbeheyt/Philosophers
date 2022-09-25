/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 04:41:55 by pbeheyt           #+#    #+#             */
/*   Updated: 2022/09/25 06:51:19 by pbeheyt          ###   ########.fr       */
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

struct s_philosopher;

typedef struct	s_data
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
}				t_data;

typedef struct	s_philosopher
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

/*error_handler.c*/
int		print_error(int error);

/*utlis.c*/
int			ft_atoi(const char *str, int *error);
void		ft_putstr_fd(char *s, int fd);
void 		print(t_data *data, int i, char *msg);

/*init.c*/
int		init(t_data *data, int ac, char **av);

/*routine.c*/
void	*routine(void *void_arg);

/*solve.c*/
void	solve(t_data *data);

/*time.c*/
long long	get_current_time(void);

#endif