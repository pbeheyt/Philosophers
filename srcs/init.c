/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 01:56:10 by pbeheyt           #+#    #+#             */
/*   Updated: 2022/09/24 09:57:47 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

int set_param(t_data *data, char **av)
{
	data->nb_philosophers = ft_atoi(av[1], &data->error);
	data->time_to_die = ft_atoi(av[2], &data->error);
	data->time_to_eat = ft_atoi(av[3], &data->error);
	data->time_to_sleep = ft_atoi(av[4], &data->error);
	if (av[5])
		data->nb_meals = ft_atoi(av[5], &data->error);
	else
		data->nb_meals = -1;
	if (data->error)
		return (print_error(11));
	return (0);
}

int	init_philosophers(t_data *data)
{
	int				i;
	t_philosopher 	*philosophers;
	
	philosophers = malloc(sizeof(t_philosopher) * data->nb_philosophers);
	if (!philosophers)
		return(print_error(9));
	i = -1;
	while (++i < data->nb_philosophers)
	{
		philosophers[i].i = i;
		philosophers[i].nb_meals = 0;
		philosophers[i].lfork_i = i;
		philosophers[i].rfork_i = (i + 1) % data->nb_philosophers;
		philosophers[i].time_last_meal = 0;
		philosophers[i].data = data;
	}
	data->philosophers = philosophers;
	return (0);
}

static int	init_mutex(t_data *data)
{
	int 			i;
	pthread_mutex_t	*forks;
	
	forks = malloc(sizeof(pthread_mutex_t) * data->nb_philosophers);
	if (!forks)
		return (print_error(9));
	i = -1;
	while (++i < data->nb_philosophers)
	{
		if (pthread_mutex_init(&(forks[i]), NULL))
			return(print_error(3));
	}
	data->m_forks = forks;
	if (pthread_mutex_init(&(data->m_print), NULL))
			return(print_error(3));
	if (pthread_mutex_init(&(data->m_is_dead), NULL))
			return(print_error(3));
	return (0);
}

int	init(t_data *data, int ac, char **av)
{
	data->error = 0;
	if (ac != 5 && ac != 6)
		return(print_error(2));
	data->has_died = 0;
	data->all_ate = 0;	
	if (set_param(data, av) || init_philosophers(data) || init_mutex(data))
		return (1);
	return (0);
}
