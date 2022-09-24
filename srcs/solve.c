/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 01:56:10 by pbeheyt           #+#    #+#             */
/*   Updated: 2022/09/24 10:11:05 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"


static int	philo_take_fork(t_philosopher *philosopher)
{
	pthread_mutex_lock(&philosopher->data->m_forks[philosopher->lfork_i]);
	print(philosopher->data, philosopher->i, "has taken a fork");
	pthread_mutex_lock(&philosopher->data->m_forks[philosopher->rfork_i]);
	print(philosopher->data, philosopher->i, "has taken a fork");

	return (0);
}

static int	philo_eat(t_philosopher *philosopher)
{
	print(philosopher->data, philosopher->i, "is eating");
	philosopher->nb_meals += 1;
	pthread_mutex_unlock(&philosopher->data->m_forks[philosopher->lfork_i]);
	pthread_mutex_unlock(&philosopher->data->m_forks[philosopher->rfork_i]);
	return (0);
}

static int	philo_sleep_and_think(t_philosopher *philosopher)
{
	print(philosopher->data, philosopher->i, "is sleeping");
	usleep(philosopher->data->time_to_sleep * 1000);
	print(philosopher->data, philosopher->i, "is thinking");
	return (0);
}
	

void	*routine(void *void_arg)
{
	t_philosopher philosopher;

	philosopher = *(t_philosopher *)void_arg;
	if (philosopher.i % 2 == 0)
		usleep(15000);
	philosopher.time_last_meal = get_current_time();
	while (philosopher.data->has_died != 1 && philosopher.data->all_ate != 1)
	{
		philo_take_fork(&philosopher);
		philo_eat(&philosopher);
		philo_sleep_and_think(&philosopher);
	}
	return(NULL);
}

// static int	all_eaten(t_data *data)
// {
	
// }

static int	is_dead(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_philosophers && !(data->has_died))
	{
		pthread_mutex_lock(&data->m_is_dead);
		if (get_current_time() - data->philosophers[i].time_last_meal > data->time_to_die)
		{
			print(data, data->philosophers[i].i, " has died");
			data->has_died = 1;
		}
		pthread_mutex_unlock(&data->m_is_dead);
		usleep(100);
	}
	return (0);
}

void	solve(t_data *data)
{
	int				i;

	data->launch_time = get_current_time();
	i = -1;
	while (++i < data->nb_philosophers)
		pthread_create(&(data->philosophers[i].thread), NULL, routine, (&(data->philosophers[i])));
	while (1)
	{
		usleep(50);
		is_dead(data);
	}

}
