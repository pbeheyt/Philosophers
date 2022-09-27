/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 01:56:10 by pbeheyt           #+#    #+#             */
/*   Updated: 2022/09/27 18:56:35 by pbeheyt          ###   ########.fr       */
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
			return (1);
	}
	return (0);
}

static int	check_end_condition(t_data *data)
{
	int	i;
	// int	j;
	
	i = 0;
	while (!(data->has_died) && !(data->all_ate))
	{
		pthread_mutex_lock(&(data->m_eat));
		if (((get_current_time() - data->phi[i].time_last_meal) > data->time_to_die))
		{
			print(data, data->phi[i].i, "has died");
			data->has_died = 1;
			return (1);
		}
		pthread_mutex_unlock(&(data->m_eat));
		if (check_meals_eaten(data, &data->phi[i]))
		{
			// j = -1;
			// while (++j < data->nb_phi)
			// {
			// 	printf("phi %d ate %d time\n", data->phi[j].i ,data->phi[j].nb_meals);	data->all_ate = 1;
			// }
			data->all_ate = 1;
			return (1);
		}
	i++;
	if (i >= data->nb_phi)
		i = 0;
	}
	return (0);
}

void	solve(t_data *data)
{
	int				i;

	data->launch_time = get_current_time();
	i = -1;
	while (++i < data->nb_phi)
	{
		pthread_create(&(data->phi[i].thread), NULL, routine, &(data->phi[i]));
		data->phi[i].time_last_meal = get_current_time();
	}
	while (1)
	{
		usleep(50);
		if (check_end_condition(data))
			return ;
	}
}

