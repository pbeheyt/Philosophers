/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 01:56:10 by pbeheyt           #+#    #+#             */
/*   Updated: 2022/10/09 03:25:49 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

void	clear_all(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_phi && data->phi)
	{
		if (data->phi[i].thread)
			pthread_join(data->phi[i].thread, NULL);
	}
	i = -1;
	while (++i < data->nb_phi && data->m_forks)
	{
		if (&(data->m_forks[i]))
			pthread_mutex_destroy(&(data->m_forks[i]));
	}
	if (&(data->m_eat))
		pthread_mutex_destroy(&(data->m_eat));
	if (&(data->m_print))
		pthread_mutex_destroy(&(data->m_print));
	if (data->phi)
		free(data->phi);
	if (data->m_forks)
		free(data->m_forks);
}
