/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 01:56:10 by pbeheyt           #+#    #+#             */
/*   Updated: 2022/10/11 05:14:29 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

static int	phi_start_eating(t_philosopher *phi)
{
	pthread_mutex_lock(&(phi->data->m_forks[phi->lfork_i]));
	print(phi->data, phi->i, "has taken a fork");
	if (phi->data->nb_phi == 1)
	{
		pthread_mutex_unlock(&(phi->data->m_forks[phi->lfork_i]));
		return (1);
	}
	pthread_mutex_lock(&(phi->data->m_forks[phi->rfork_i]));
	print(phi->data, phi->i, "has taken a fork");
	pthread_mutex_lock(&(phi->data->m_eat));
	print(phi->data, phi->i, "is eating");
	phi->time_last_meal = get_curr_time();
	phi->nb_meals += 1;
	pthread_mutex_unlock(&(phi->data->m_eat));
	custom_usleep(phi->data, phi->data->time_to_eat);
	print(phi->data, phi->i, "is sleeping");
	pthread_mutex_unlock(&(phi->data->m_forks[phi->lfork_i]));
	pthread_mutex_unlock(&(phi->data->m_forks[phi->rfork_i]));
	custom_usleep(phi->data, phi->data->time_to_sleep);
	print(phi->data, phi->i, "is thinking");
	return (0);
}

void	*routine(void *void_arg)
{
	t_philosopher	*phi;

	phi = (t_philosopher *)void_arg;
	if (!(phi->i % 2))
		usleep(PHILO_WAIT_TO_START);
	while (!phi->data->has_died && !phi->data->all_ate)
	{
		if (phi_start_eating(phi))
			return (NULL);
	}
	return (NULL);
}
