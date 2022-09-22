/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 01:56:10 by pbeheyt           #+#    #+#             */
/*   Updated: 2022/09/22 09:16:45 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

void	error_handler(int error)
{
	if (error = 1)
		ft_putstr_fd("Error\nInvalid number of arguments", 2);
	if (error = 2)
		ft_putstr_fd("Error\nFailed to initialise mutex", 2);
	if (error = 9)
		ft_putstr_fd("Error\nMemory allocation failed", 2);
	if (error = 11)
		ft_putstr_fd("Error\nWrong set of arguments", 2);
}