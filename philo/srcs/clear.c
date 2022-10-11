/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 01:56:10 by pbeheyt           #+#    #+#             */
/*   Updated: 2022/10/09 08:30:48 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

static void	join_threads(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->cs->threads)
		pthread_join(data->phi[i].thread, NULL);
}

static void	destroy_mutex(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->cs->m_forks)
		pthread_mutex_destroy(&(data->m_forks[i]));
	if (data->cs->m_eat)
		pthread_mutex_destroy(&(data->m_eat));
	if (data->cs->m_print)
		pthread_mutex_destroy(&(data->m_print));
}

void	clear_all(t_data *data)
{
	join_threads(data);
	destroy_mutex(data);
	if (data->m_forks)
		free(data->m_forks);
	if (data->phi)
		free(data->phi);
	if (data->cs)
		free(data->cs);
}
