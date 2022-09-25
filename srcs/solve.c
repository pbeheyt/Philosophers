/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 01:56:10 by pbeheyt           #+#    #+#             */
/*   Updated: 2022/09/25 06:58:07 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

static void	check_meals_eaten(t_philosopher *phi)
{
	int	total_meals;

	total_meals = phi->data->nb_meals;
	if (phi->nb_meals == total_meals)
		phi->done_eating = 1;
}

static int	check_end_condition(t_data *data)
{
	int	nb_phi_done_eating;
	int	i;
	
	nb_phi_done_eating = 0;
	i = 0;
	while (!(data->has_died))
	{
		// printf("%d : %lld\n",data->phi[i].i, data->phi[i].time_last_meal);
		pthread_mutex_lock(&data->m_eat);
		if ((get_current_time() - data->phi[i].time_last_meal) > data->time_to_die)
		{
			printf("launch time : %lld\n", data->launch_time);
			printf("%lld - %lld = %lld\n", get_current_time(), data->phi[3].time_last_meal, get_current_time() - data->phi[3].time_last_meal);
			print(data, data->phi[i].i, "has died");
			data->has_died = 1;
			return (1);
		}
		pthread_mutex_unlock(&data->m_eat);
		check_meals_eaten(&data->phi[i]);
		if (nb_phi_done_eating == data->nb_phi)
			return (1);
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
		pthread_create(&(data->phi[i].thread), NULL, routine, (&(data->phi[i])));
		data->phi[i].time_last_meal = get_current_time();
	}
	while (1)
	{
		usleep(50);
		if (check_end_condition(data))
			return ;
	}
}
