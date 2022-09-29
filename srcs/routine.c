/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 01:56:10 by pbeheyt           #+#    #+#             */
/*   Updated: 2022/09/29 12:10:03 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

static void	unlock_mutex(t_philosopher *phi, int ret)
{
	if (ret >= 3)
		pthread_mutex_unlock(&(phi->data->m_eat));
	if (ret >= 2)
		pthread_mutex_unlock(&(phi->data->m_forks[phi->rfork_i]));
	if (ret >= 1)
		pthread_mutex_unlock(&(phi->data->m_forks[phi->lfork_i]));
}

static int	phi_eat(t_philosopher *phi)
{
	pthread_mutex_lock(&(phi->data->m_forks[phi->lfork_i]));
	if (phi->data->has_died || phi->data->all_ate)
		return (1);
	print(phi->data, phi->i, "has taken a fork");
	pthread_mutex_lock(&(phi->data->m_forks[phi->rfork_i]));
	if (phi->data->has_died || phi->data->all_ate)
		return (2);
	print(phi->data, phi->i, "has taken a fork");
	pthread_mutex_lock(&(phi->data->m_eat));
	if (phi->data->has_died || phi->data->all_ate)
		return (3);
	print(phi->data, phi->i, "is eating");
	phi->time_last_meal = get_current_time();
	phi->nb_meals += 1;
	pthread_mutex_unlock(&(phi->data->m_eat));
	usleep(phi->data->time_to_eat * 1000);
	pthread_mutex_unlock(&(phi->data->m_forks[phi->lfork_i]));
	pthread_mutex_unlock(&(phi->data->m_forks[phi->rfork_i]));
	return (0);
}

static void	phi_sleep_and_think(t_philosopher *phi)
{
	if (phi->data->has_died || phi->data->all_ate)
		return ;
	print(phi->data, phi->i, "is sleeping");
	usleep(phi->data->time_to_sleep * 1000);
	if (phi->data->has_died || phi->data->all_ate)
		return ;
	print(phi->data, phi->i, "is thinking");
}

void	*routine(void *void_arg)
{
	t_philosopher	*phi;
	int				ret;

	phi = (t_philosopher *)void_arg;
	if (phi->i % 2 == 0)
		usleep(PHILO_WAIT_TO_START);
	while (!phi->data->has_died && !phi->data->all_ate)
	{
		ret = phi_eat(phi);
		if (ret)
			return (unlock_mutex(phi, ret), NULL);
		phi_sleep_and_think(phi);
	}
	return (NULL);
}
