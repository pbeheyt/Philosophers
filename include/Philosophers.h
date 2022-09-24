/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 04:41:55 by pbeheyt           #+#    #+#             */
/*   Updated: 2022/09/24 08:16:40 by pbeheyt          ###   ########.fr       */
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


typedef struct	s_philosopher
{
	int			i;
	int			nb_meals;
	int			lfork_i;
	int			rfork_i;
	long long	time_last_meal;
	pthread_t	thread;
	t_data		*data;
}				t_philosopher;

typedef struct	s_data
{
	int				error;
	int				nb_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_meals;
	int				has_died;
	int				all_ate;
	long long		launch_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	t_philosopher	*philosophers;
}				t_data;

/*error_handler.c*/
int		print_error(int error);

/*utlis.c*/
int			ft_atoi(const char *str, int *error);
void		ft_putstr_fd(char *s, int fd);
long long	get_current_time(void);
void 		print(t_data * data, int i, char *msg);

/*init.c*/
int		init(t_data *data, int ac, char **av);

/*solve.c*/
void	solve(t_data *data);


#endif