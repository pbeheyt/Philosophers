/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilis.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 01:56:10 by pbeheyt           #+#    #+#             */
/*   Updated: 2022/10/12 05:56:43 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

long long	get_curr_time(void)
{
	struct timeval	current;

	gettimeofday(&current, NULL);
	return (current.tv_sec * 1000 + current.tv_usec / 1000);
}

void	custom_usleep(t_data *data, int ms)
{
	long	start;
	long	end;

	start = get_curr_time();
	end = get_curr_time();
	while (end - start < ms)
	{
		if (data->has_died)
			return ;
		usleep(WAIT_CUSTOM_SLEEP);
		end = get_curr_time();
	}
}

void	print(t_data *data, int i, int died, char *msg)
{
	pthread_mutex_lock(&(data->m_print));
	if (!data->error && !data->has_died && !data->all_ate)
	{
		printf("%lld ", get_curr_time() - data->launch_time);
		printf("%d ", i + 1);
		printf("%s\n", msg);
		if (died == 1)
			data->has_died = 1;
	}
	pthread_mutex_unlock(&(data->m_print));
}
