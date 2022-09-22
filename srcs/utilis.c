/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilis.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 01:56:10 by pbeheyt           #+#    #+#             */
/*   Updated: 2022/09/22 08:40:09 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

int	ft_atoi(const char *str, int *error)
{
	int			i;
	int			sign;
	long long	result;
	int			tmp;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
	{	
		sign = -sign;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		result = result * 10 + str[i++] - '0';
	result *= sign;
	tmp = (int)result;
	if (str[i] || result != tmp || (sign > 0 && ft_strlen(str) > 10)
		|| (sign < 0 && ft_strlen(str) > 11))
		*error = 11;
	return (result);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	if (fd < 0 || !s)
		return ;
	i = -1;
	while (s[++i])
		write(fd, &s[i], 1);
}