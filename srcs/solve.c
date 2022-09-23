/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 01:56:10 by pbeheyt           #+#    #+#             */
/*   Updated: 2022/09/23 08:53:14 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

void	*routine(void *void_arg)
{
	(void)void_arg;
	return(NULL);
}

void	solve(t_data *data)
{
	int				i;
	t_philosopher	*philosophers;

	philosophers = data->philosophers;
	data->launch_time = get_current_time();
	i = -1;
	while (++i < data->nb_philosophers)
	{
		pthread_create(&(philosophers[i].thread), NULL, routine, (&(philosophers[i])));
	}
}
