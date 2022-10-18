/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 01:56:10 by pbeheyt           #+#    #+#             */
/*   Updated: 2022/10/19 01:45:44 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

int	error_handler(t_data *data, int error, int clear)
{
	data->error = error;
	if (clear && data->cs->m_print)
		pthread_mutex_lock(&(data->m_print));
	if (error == NB_ARGS_ERROR)
		ft_putstr_fd("Error\nInvalid number of arguments\n", 2);
	if (error == NB_PHILO_ERROR)
		ft_putstr_fd("Error\nInvalid number of philosophers\n", 2);
	if (error == ARGS_ERROR)
		ft_putstr_fd("Error\nWrong set of arguments\n", 2);
	if (error == MIN_TIME_ERROR)
		ft_putstr_fd("Error\nTime to sleep/eat must be at least 10ms\n", 2);
	if (error == MUTEX_ERROR)
		ft_putstr_fd("Error\nFailed to initialize mutex\n", 2);
	if (error == THREAD_ERROR)
		ft_putstr_fd("Error\nFailed to create thread\n", 2);
	if (error == ALLOC_ERROR)
		ft_putstr_fd("Error\nMemory allocation failed\n", 2);
	if (clear && data->cs->m_print)
		pthread_mutex_unlock(&(data->m_print));
	if (clear)
		clear_all(data);
	return (error);
}
