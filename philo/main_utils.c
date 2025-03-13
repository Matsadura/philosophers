/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaoui <zzaoui@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 10:23:38 by zzaoui            #+#    #+#             */
/*   Updated: 2025/03/13 08:40:24 by zzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * current_time_milis - Calculate the current time in milliseconds
 * Return: The current time
 */
long long   current_time_milis(void)
{
	struct timeval  tv;
	gettimeofday(&tv, NULL);
	return ((long long)(tv.tv_sec) * 1000 + (tv.tv_usec / 1000));
}

/**
 * better_usleep - A more precise sleeping function based on chunks
 * @ms: Time to sleep
 */
void	better_usleep(long long ms, t_data *data)
{
	long long	start;
	long long	elapsed;

	start = current_time_milis();
	while (1)
	{
		elapsed = current_time_milis() - start;
	    if (elapsed >= ms)
	    	break ;
	    usleep(500);
	    pthread_mutex_lock(&data->sim_mutex);
	    if (data->sim_stop == TRUE)
	    {
	    	pthread_mutex_unlock(&data->sim_mutex);
	    	break ;
	    }
	    pthread_mutex_unlock(&data->sim_mutex);
	}
}