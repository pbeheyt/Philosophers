/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilis.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 01:56:10 by pbeheyt           #+#    #+#             */
/*   Updated: 2022/09/23 02:53:08 by pbeheyt          ###   ########.fr       */
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

long long	get_current_time(void)
{
	struct timeval	current;
	long long		result;
	
	gettimeofday(&current, NULL);
	result = current.tv_sec * 1000 + current.tv_usec / 1000;
	return (result);
}

void print(t_data * data, char *msg, int i)
{
    long long time;
    
    time = get_current_time() - data->launch_time;
    pthread_mutex_lock(&(data->print));
    printf("%lld ", time);
    printf("%d ", i + 1);
    printf("%s\n", msg);
    pthread_mutex_unlock(&(data->print));
    
}