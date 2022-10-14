/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 01:56:10 by pbeheyt           #+#    #+#             */
/*   Updated: 2022/10/14 08:54:27 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

static void	unlock_mutex(t_philosopher *phi, int lock)
{
	if (lock <= 1)
		pthread_mutex_unlock(&(phi->data->m_forks[phi->rfork_i]));
	if (lock <= 2)
		pthread_mutex_unlock(&(phi->data->m_forks[phi->lfork_i]));	
}

static int	phi_start_eating(t_philosopher *phi)
{
	pthread_mutex_lock(&(phi->data->m_forks[phi->lfork_i]));
	if (print(phi->data, phi->i, 0, "has taken a fork"))
		return (unlock_mutex(phi, 2), 1);
	if (phi->data->nb_phi == 1)
		return (unlock_mutex(phi, 2), 1);
	pthread_mutex_lock(&(phi->data->m_forks[phi->rfork_i]));
	if (print(phi->data, phi->i, 0, "has taken a fork"))
		return (unlock_mutex(phi, 1), 1);
	if (print(phi->data, phi->i, 0, "is eating"))
		return (unlock_mutex(phi, 1), 1);
	pthread_mutex_lock(&(phi->data->m_eat));
	phi->time_last_meal = get_curr_time();
	phi->nb_meals += 1;
	pthread_mutex_unlock(&(phi->data->m_eat));
	custom_usleep(phi->data, phi->data->time_to_eat);
	if (print(phi->data, phi->i, 0, "is sleeping"))
		return (unlock_mutex(phi, 1), 1);
	pthread_mutex_unlock(&(phi->data->m_forks[phi->rfork_i]));
	pthread_mutex_unlock(&(phi->data->m_forks[phi->lfork_i]));
	custom_usleep(phi->data, phi->data->time_to_sleep);
	print(phi->data, phi->i, 0, "is thinking");
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
		if (phi_start_eating(phi))
			return (NULL);
		if (phi->data->nb_phi % 2)
			usleep(PHILO_WAIT);
	}
	return (NULL);
}
