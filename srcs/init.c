/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 01:56:10 by pbeheyt           #+#    #+#             */
/*   Updated: 2022/09/23 09:42:11 by pbeheyt          ###   ########.fr       */
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
		return (error_handler(11), 11);
	return (0);
}

int	init_philosophers(t_data *data)
{
	int				i;
	t_philosopher 	*philosophers;
	
	philosophers = malloc(sizeof(t_philosopher) * data->nb_philosophers);
	if (!philosophers)
		return(error_handler(9), 9);
	i = -1;
	while (++i < data->nb_philosophers)
	{
		philosophers[i].i = i;
		philosophers[i].nb_meals = 0;
		philosophers[i].lfork_i = i;
		philosophers[i].rfork_i = (i + 1) % data->nb_philosophers;
		philosophers[i].time_last_meal = 0;
	}
	data->philosophers = philosophers;
	return (0);
}

static int	init_mutex(t_data *data)
{
	int i;

	i = -1;
	while (++i < data->nb_philosophers)
	{
		if (pthread_mutex_init(&(data->forks[i]), NULL))
			return(error_handler(3), 3);
	}
	if (pthread_mutex_init(&(data->print), NULL))
			return(error_handler(3), 3);
	return (0);
}

int	init(t_data *data, int ac, char **av)
{
	data->error = 0;
	if (ac != 5 && ac != 6)
		return(error_handler(2), 2);
	data->has_died = 0;
	data->all_ate = 0;	
	if (set_param(data, av) || init_philosophers(data) || init_mutex(data))
		return (1);
	return (0);
}
