/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaoui <zzaoui@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 10:23:38 by zzaoui            #+#    #+#             */
/*   Updated: 2025/03/11 12:24:41 by zzaoui           ###   ########.fr       */
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
	return ((long long)(tv.tv_sec) * 1000LL + (tv.tv_usec / 1000LL));
}

/**
 * better_usleep - A more precise sleeping function based on chunks
 * @ms: Time to sleep
 */
void	better_usleep(long long ms)
{
	long long	start;

	start = current_time_milis();
	while (ms > current_time_milis() - start)
		usleep(500);
}