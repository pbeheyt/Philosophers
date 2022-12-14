/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilis.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 01:56:10 by pbeheyt           #+#    #+#             */
/*   Updated: 2022/10/16 04:30:18 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

long long	get_curr_time(void)
{
	struct timeval	current;

	gettimeofday(&current, NULL);
	return (current.tv_sec * 1000 + current.tv_usec / 1000);
}

static int	check_end(t_data *data)
{
	pthread_mutex_lock(&(data->m_end));
	if (data->error || data->has_died || data->all_ate)
		return (pthread_mutex_unlock(&(data->m_end)), 1);
	pthread_mutex_unlock(&(data->m_end));
	return (0);
}

void	custom_usleep(t_data *data, long long ms)
{
	long long	start_time;

	start_time = get_curr_time();
	while (!check_end(data))
	{
		if ((get_curr_time() - start_time) >= ms)
			break ;
		usleep(WAIT_CUSTOM_SLEEP);
	}
}

int	print(t_data *data, int i, int died, char *msg)
{
	pthread_mutex_lock(&(data->m_print));
	if (check_end(data))
		return (pthread_mutex_unlock(&(data->m_print)), 1);
	printf("%lld %d %s\n", get_curr_time() - data->launch_time, i + 1, msg);
	if (died == 1)
	{
		pthread_mutex_lock(&(data->m_end));
		data->has_died = 1;
		pthread_mutex_unlock(&(data->m_end));
	}
	pthread_mutex_unlock(&(data->m_print));
	return (0);
}
