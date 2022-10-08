/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 01:56:10 by pbeheyt           #+#    #+#             */
/*   Updated: 2022/10/08 03:56:03 by pbeheyt          ###   ########.fr       */
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

	i = 0;
	while (!data->has_died && !data->all_ate)
	{
		usleep(WAIT_CHECK_END_LOOP);
		pthread_mutex_lock(&(data->m_eat));
		if (get_current_time() - data->phi[i].time_last_meal
			> data->time_to_die)
		{
			pthread_mutex_unlock(&(data->m_eat));
			print(data, data->phi[i].i, "died");
			data->has_died = 1;
			return (1);
		}
		if (check_meals_eaten(data, &data->phi[i]))
		{
			data->all_ate = 1;
			return (1);
		}
		pthread_mutex_unlock(&(data->m_eat));
		if (++i >= data->nb_phi)
			i = 0;
	}
	return (0);
}

int	solve(t_data *data)
{
	int				i;

	data->launch_time = get_current_time();
	i = -1;
	while (++i < data->nb_phi)
	{
		if (pthread_create(&(data->phi[i].thread),
				NULL, routine, &(data->phi[i])))
			return (clear_all(data), error_handler(data, THREAD_ERROR));
		data->phi[i].time_last_meal = get_current_time();
	}
	while (1)
	{
		if (check_end_condition(data))
			return (clear_all(data), 0);
	}
	return (0);
}

			// j = -1;
			// while (++j < data->nb_phi)
			// {
			// 	printf("phi %d ate %d time\n", data->phi[j].i,
			// 		data->phi[j].nb_meals);
			// }