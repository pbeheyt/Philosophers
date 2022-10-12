/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 01:56:10 by pbeheyt           #+#    #+#             */
/*   Updated: 2022/10/12 06:17:14 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

int	set_param(t_data *data, char **av)
{
	data->nb_phi = ft_atoi(av[1], &data->error);
	if (!(data->nb_phi > 0 && data->nb_phi <= 200))
		return (error_handler(data, NB_PHILO_ERROR, 1));
	data->time_to_die = ft_atoi(av[2], &data->error);
	data->time_to_eat = ft_atoi(av[3], &data->error);
	data->time_to_sleep = ft_atoi(av[4], &data->error);
	if (data->time_to_eat < 30 || data->time_to_sleep < 30)
		return (error_handler(data, MIN_TIME_ERROR, 1));
	if (av[5])
	{
		data->nb_meals = ft_atoi(av[5], &data->error);
		if (!data->nb_meals)
			return (error_handler(data, ARGS_ERROR, 1));
	}
	else
		data->nb_meals = -1;
	if (data->error)
		return (error_handler(data, ARGS_ERROR, 1));
	return (0);
}

int	init_philosophers(t_data *data)
{
	int				i;

	if (data->error)
		return (data->error);
	data->phi = malloc(sizeof(t_philosopher) * data->nb_phi);
	if (!data->phi)
		return (error_handler(data, ALLOC_ERROR, 1));
	i = -1;
	while (++i < data->nb_phi)
	{
		data->phi[i].i = i;
		data->phi[i].nb_meals = 0;
		data->phi[i].lfork_i = i;
		data->phi[i].rfork_i = (i + 1) % data->nb_phi;
		data->phi[i].time_last_meal = 0;
		data->phi[i].done_eating = 0;
		data->phi[i].data = data;
	}
	return (0);
}

static int	init_mutex(t_data *data)
{
	int	i;

	if (data->error)
		return (data->error);
	data->m_forks = malloc(sizeof(pthread_mutex_t) * data->nb_phi);
	if (!data->m_forks)
		return (error_handler(data, ALLOC_ERROR, 1));
	i = -1;
	while (++i < data->nb_phi)
	{
		if (pthread_mutex_init(&(data->m_forks[i]), NULL))
			return (error_handler(data, MUTEX_ERROR, 1));
		data->cs->m_forks += 1;
	}
	if (pthread_mutex_init(&(data->m_print), NULL))
		return (error_handler(data, MUTEX_ERROR, 1));
	data->cs->m_print = 1;
	if (pthread_mutex_init(&(data->m_eat), NULL))
		return (error_handler(data, MUTEX_ERROR, 1));
	data->cs->m_eat = 1;
	return (0);
}

int	init(t_data *data, int ac, char **av)
{
	data->error = 0;
	if (ac != 5 && ac != 6)
		return (error_handler(data, NB_ARGS_ERROR, 0));
	data->cs = malloc(sizeof(t_check_status));
	if (!data->cs)
		return (error_handler(data, ALLOC_ERROR, 0));
	data->cs->m_eat = 0;
	data->cs->m_print = 0;
	data->cs->m_forks = 0;
	data->cs->threads = 0;
	data->has_died = 0;
	data->all_ate = 0;
	data->m_forks = 0;
	data->phi = 0;
	if (set_param(data, av) || init_philosophers(data) || init_mutex(data))
		return (data->error);
	return (0);
}
