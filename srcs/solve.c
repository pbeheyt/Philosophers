/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 01:56:10 by pbeheyt           #+#    #+#             */
/*   Updated: 2022/09/24 08:49:47 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"


static int	philo_take_fork(t_philosopher *philosopher)
{
	pthread_mutex_lock(&philosopher->data->forks[philosopher->lfork_i]);
	print(&philosopher->data, philosopher->i, "has taken a fork");
	pthread_mutex_lock(&philosopher->data->forks[philosopher->rfork_i]);
	print(&philosopher->data, philosopher->i, "has taken a fork");

	return (0);
}

static int	philo_eat(t_philosopher *philosopher)
{
	print(&philosopher->data, philosopher->i, "is eating");
	philosopher->nb_meals += 1;
	pthread_mutex_unlock(&philosopher->data->forks[philosopher->lfork_i]);
	pthread_mutex_unlock(&philosopher->data->forks[philosopher->rfork_i]);
	
}

static int	philo_sleep_and_think(t_philosopher *philosopher)
{
	print(&philosopher->data, philosopher->i, "is sleeping");
	usleep(200);
	print(&philosopher->data, philosopher->i, "is thinking");
}
	

void	*routine(void *void_arg)
{
	t_philosopher philosopher;

	philosopher = *(t_philosopher *)void_arg;
	if (philosopher.i % 2 == 0)
		usleep(10);
	philosopher.time_last_meal = get_current_time();
	while (philosopher.data->has_died != 1 && philosopher.data->all_ate != 1)
	{
		philo_take_fork(&philosopher);
		philo_eat(&philosopher);
		philo_sleep_and_think(&philosopher);
	}
	return(NULL);
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
		usleep(5);
		
	}

}
