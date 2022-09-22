/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 01:56:10 by pbeheyt           #+#    #+#             */
/*   Updated: 2022/09/22 08:48:13 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

void	error_handler(int error)
{
	if (error = 1)
		ft_putstr("Error\nInvalid number of arguments");
	if (error = 2)
		ft_putstr("Error\nFailed to initialise mutex");
	if (error = 9)
		ft_putstr("Error\nMemory allocation failed");
	if (error = 11)
		ft_putstr("Error\nWrong set of arguments");
}