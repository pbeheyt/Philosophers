/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 01:56:10 by pbeheyt           #+#    #+#             */
/*   Updated: 2022/09/25 09:32:10 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"


static void	phi_eat(t_philosopher *phi)
{
	pthread_mutex_lock(&(phi->data->m_forks[phi->lfork_i]));
	print(phi->data, phi->i, "has taken a fork");
	pthread_mutex_lock(&(phi->data->m_forks[phi->rfork_i]));
	print(phi->data, phi->i, "has taken a fork");
	pthread_mutex_lock(&(phi->data->m_eat));
	print(phi->data, phi->i, "is eating");
	phi->time_last_meal = get_current_time();
	pthread_mutex_unlock(&(phi->data->m_eat));
	usleep(phi->data->time_to_eat * 1000);
	phi->nb_meals += 1;
	pthread_mutex_unlock(&(phi->data->m_forks[phi->lfork_i]));
	pthread_mutex_unlock(&(phi->data->m_forks[phi->rfork_i]));
}

static void	phi_sleep_and_think(t_philosopher *phi)
{
	print(phi->data, phi->i, "is sleeping");
	usleep(phi->data->time_to_sleep * 1000);
	print(phi->data, phi->i, "is thinking");
}

void	*routine(void *void_arg)
{
	t_philosopher *phi;

	phi = (t_philosopher *)void_arg;
	if (phi->i % 2 == 0)
		usleep(15000);
	while (phi->data->has_died != 1 && phi->data->all_ate != 1)
	{
		phi_eat(phi);
		phi_sleep_and_think(phi);
	}
	return(NULL);
}

