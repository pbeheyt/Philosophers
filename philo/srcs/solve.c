/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 01:56:10 by pbeheyt           #+#    #+#             */
/*   Updated: 2022/10/12 06:26:56 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

static int	check_meals_eaten(t_data *data, t_philosopher *phi)
{
	int				j;

	if (phi->nb_meals == data->nb_meals)
		phi->done_eating = 1;
	j = -1;
	while (data->phi[++j].done_eating == 1)
	{
		if (j == data->nb_phi - 1)
		{
			data->all_ate = 1;
			return (1);
		}
	}
	return (0);
}

static void	check_end_condition(t_data *data)
{
	int	i;

	i = 0;
	while (1)
	{
		usleep(WAIT_CHECK_END_LOOP);
		pthread_mutex_lock(&(data->m_eat));
		if (get_curr_time() - data->phi[i].time_last_meal > data->time_to_die)
		{
			print(data, data->phi[i].i, 1, "died");
			pthread_mutex_unlock(&(data->m_eat));
			return ;
		}
		if (check_meals_eaten(data, &data->phi[i]))
		{
			pthread_mutex_unlock(&(data->m_eat));
			return ;
		}
		pthread_mutex_unlock(&(data->m_eat));
		if (++i >= data->nb_phi)
			i = 0;
	}
}

static int	create_threads(t_data *data)
{
	int		i;

	i = -1;
	while (++i < data->nb_phi)
	{
		if (pthread_create(&(data->phi[i].thread),
				NULL, routine, &(data->phi[i])))
			return (error_handler(data, THREAD_ERROR, 1));
		data->phi[i].time_last_meal = get_curr_time();
		data->cs->threads += 1;
	}
	return (0);
}

int	solve(t_data *data)
{
	data->launch_time = get_curr_time();
	if (create_threads(data))
		return (data->error);
	check_end_condition(data);
	clear_all(data);
	return (0);
}
