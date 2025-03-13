/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaoui <zzaoui@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 09:37:13 by zzaoui            #+#    #+#             */
/*   Updated: 2025/03/13 10:34:07 by zzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * philosopher - The philosopher routine, thinks, picks forks
 *	eats, puts down forks and sleeps
 * @arg: Address of the philospher struct
 */
void	*philosopher(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(&philo->data->sim_mutex);
		if (philo->data->sim_stop == TRUE)
		{
			pthread_mutex_unlock(&philo->data->sim_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->data->sim_mutex);
		print_state(*philo, THINKING);
		pick_forks(*philo);
		eat(philo);
		put_forks(*philo);
		print_state(*philo, SLEEPING);
		better_usleep(philo->data->time_to_sleep, philo->data);
	}
	return (NULL);
}

/**
 * create_philos - Spawns philosopher threads
 * @th: The thread
 * @philos: Arrar of philo structs
 * @data: Pointer to the shared data structure
 */
void	create_philos(pthread_t **th, t_philo **philos, t_data *data)
{
	int	i;

	*th = malloc(data->n_ph * sizeof(pthread_t));
	if (*th == NULL)
		return ;
	i = 0;
	while (i < data->n_ph)
	{
		(*philos)[i].id = i + 1;
		(*philos)[i].data = data;
		pthread_create(&((*th)[i]), NULL, philosopher, &((*philos)[i]));
		usleep(100);
		i++;
	}
}
