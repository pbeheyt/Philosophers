/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 01:56:10 by pbeheyt           #+#    #+#             */
/*   Updated: 2022/10/09 07:25:24 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

int	error_handler(t_data *data, int error, int clear)
{
	data->error = error;
	if (error == NB_ARGS_ERROR)
		ft_putstr_fd("Error\nInvalid number of arguments", 2);
	if (error == NB_PHILO_ERROR)
		ft_putstr_fd("Error\nInvalid number of philosophers", 2);
	if (error == ARGS_ERROR)
		ft_putstr_fd("Error\nWrong set of arguments", 2);
	if (error == MUTEX_ERROR)
		ft_putstr_fd("Error\nFailed to initialize mutex", 2);
	if (error == THREAD_ERROR)
		ft_putstr_fd("Error\nFailed to create thread", 2);
	if (error == ALLOC_ERROR)
		ft_putstr_fd("Error\nMemory allocation failed", 2);
	if (clear)
		clear_all(data);
	return (error);
}
