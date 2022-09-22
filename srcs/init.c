/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 01:56:10 by pbeheyt           #+#    #+#             */
/*   Updated: 2022/09/22 08:47:46 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

static void set_param(t_data *data, char **av)
{
	data->nb_philosophers = ft_atoi(av[1], data->error);
	data->time_to_die = ft_atoi(av[2], data->error);
	data->time_to_eat = ft_atoi(av[3], data->error);
	data->time_to_sleep = ft_atoi(av[4], data->error);
	if (av[5])
		data->nb_meals = ft_atoi(av[5], data->error);
	else
		data->nb_meals = -1;

}

void	init_philosophers(t_data *data)
{
	int				i;
	t_philosopher 	*philosophers;
	
	philosophers = malloc(sizeof(t_philosopher) * data->nb_philosophers);
	if (!philosophers)
	{
		data->error = 9;	
		return ;
	}
	i = -1;
	while (++i < data->nb_philosophers)
	{
		data->philosophers[i].i = i;
		data->philosophers[i].nb_meals = 0;
		data->philosophers[i].lfork_i = i;
		data->philosophers[i].rfork_i = (i + 1) % data->nb_philosophers;
		data->philosophers[i].time_last_meal = 0;
	}
	data->philosophers = philosophers;
}

void init_mutex(t_data *data)
{
	int i;

	i = -1;
	while (++i < data->nb_philosophers)
	{
		if (pthread_mutex_init(&(data->forks[i]), NULL))
		{
			data->error = 2;	
			return ;
		}
	}
	if (pthread_mutex_init(&(data->print), NULL))
	{
		data->error = 2;	
		return ;
	}
}

void	init(t_data *data, int ac, char **av)
{
	data->error = 0;
	if (ac != 5 && ac != 6)
		data->error = 1;
	data->has_died = 0;
	data->all_ate = 0;	
	set_param(data, av);
	init_philosophers(data);
	init_mutex(data);
}
