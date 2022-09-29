/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 01:56:10 by pbeheyt           #+#    #+#             */
/*   Updated: 2022/09/29 12:17:31 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

int	error_handler(t_data *data, int error)
{
	data->error = error;
	if (error == NB_ARGS_ERROR)
		ft_putstr_fd("Error\nInvalid number of arguments", 2);
	if (error == ARGS_ERROR)
		ft_putstr_fd("Error\nWrong set of arguments", 2);
	if (error == MUTEX_ERROR)
		ft_putstr_fd("Error\nFailed to initialize mutex", 2);
	if (error == THREAD_ERROR)
		ft_putstr_fd("Error\nFailed to create thread", 2);
	if (error == ALLOC_ERROR)
		ft_putstr_fd("Error\nMemory allocation failed", 2);
	return (error);
}
