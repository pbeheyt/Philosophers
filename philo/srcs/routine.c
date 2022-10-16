/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 01:56:10 by pbeheyt           #+#    #+#             */
/*   Updated: 2022/10/16 04:59:37 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

static int	unlock_forks_mutex(t_philosopher *phi, int lock)
{
	if (lock >= 2)
		pthread_mutex_unlock(&(phi->data->m_forks[phi->rfork_i]));
	if (lock >= 1)
		pthread_mutex_unlock(&(phi->data->m_forks[phi->lfork_i]));
	return (lock);
}

static int	phi_start_routine(t_philosopher *phi)
{
	t_data	*data;

	data = phi->data;
	pthread_mutex_lock(&(data->m_forks[phi->lfork_i]));
	if (print(data, phi->i, 0, "has taken a fork")
		|| data->nb_phi == 1)
		return (unlock_forks_mutex(phi, 1));
	pthread_mutex_lock(&(data->m_forks[phi->rfork_i]));
	if (print(data, phi->i, 0, "has taken a fork")
		|| print(data, phi->i, 0, "is eating"))
		return (unlock_forks_mutex(phi, 2));
	pthread_mutex_lock(&(data->m_eat));
	phi->time_last_meal = get_curr_time();
	phi->nb_meals += 1;
	pthread_mutex_unlock(&(data->m_eat));
	custom_usleep(data, data->time_to_eat);
	if (print(data, phi->i, 0, "is sleeping"))
		return (unlock_forks_mutex(phi, 2));
	unlock_forks_mutex(phi, 2);
	custom_usleep(data, data->time_to_sleep);
	print(data, phi->i, 0, "is thinking");
	return (0);
}

void	*routine(void *void_arg)
{
	t_philosopher	*phi;

	phi = (t_philosopher *)void_arg;
	if ((phi->i % 2))
		usleep(PHILO_WAIT);
	while (1)
	{
		if (phi_start_routine(phi))
			return (NULL);
		if (phi->data->nb_phi % 2)
			usleep(PHILO_WAIT);
	}
	return (NULL);
}
