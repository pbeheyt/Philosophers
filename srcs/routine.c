/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 01:56:10 by pbeheyt           #+#    #+#             */
/*   Updated: 2022/09/25 06:38:07 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"


static int	phi_eat(t_philosopher *phi)
{
	pthread_mutex_lock(&phi->data->m_forks[phi->lfork_i]);
	print(phi->data, phi->i, "has taken a fork");
	pthread_mutex_lock(&phi->data->m_forks[phi->rfork_i]);
	print(phi->data, phi->i, "has taken a fork");
	pthread_mutex_lock(&phi->data->m_eat);
	phi->time_last_meal = get_current_time();
	print(phi->data, phi->i, "is eating");
	// printf("%lld\n", phi->time_last_meal);
	pthread_mutex_unlock(&phi->data->m_eat);
	phi->nb_meals += 1;
	usleep(phi->data->time_to_eat * 1000);
	pthread_mutex_unlock(&phi->data->m_forks[phi->lfork_i]);
	pthread_mutex_unlock(&phi->data->m_forks[phi->rfork_i]);
	return (0);
}

static int	phi_sleep_and_think(t_philosopher *phi)
{
	print(phi->data, phi->i, "is sleeping");
	usleep(phi->data->time_to_sleep * 1000);
	print(phi->data, phi->i, "is thinking");
	return (0);
}

void	*routine(void *void_arg)
{
	t_philosopher phi;

	phi = *(t_philosopher *)void_arg;
	if (phi.i % 2 == 0)
		usleep(15000);
	while (phi.data->has_died != 1 && phi.data->all_ate != 1)
	{
		phi_eat(&phi);
		phi_sleep_and_think(&phi);
	}
	return(NULL);
}

