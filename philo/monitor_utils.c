/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaoui <zzaoui@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 10:39:21 by zzaoui            #+#    #+#             */
/*   Updated: 2025/03/13 12:35:06 by zzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * sim_stop - Set the sim stop flag to TRUE
 * @data: Pointer to the shared data structure
 */
void	sim_stop(t_data *data)
{
	pthread_mutex_lock(&data->sim_mutex);
	data->sim_stop = TRUE;
	pthread_mutex_unlock(&data->sim_mutex);
}

/**
 * starved - Check if a philospher has starved to death
 * @philo: The philosopher to check
 * Return: TRUE if starved, FALSE otherwise
 */
static int	starved(t_philo philo)
{
	long long	last_meal;

	pthread_mutex_lock(&philo.data->meal_mutex);
	last_meal = philo.data->last_time_meals[philo.id - 1];
	pthread_mutex_unlock(&philo.data->meal_mutex);
	if ((current_time_milis() - last_meal) > philo.data->time_to_die)
	{
		print_state(philo, DIED);
		pthread_mutex_lock(&philo.data->sim_mutex);
		if (philo.data->sim_stop == TRUE)
		{
			pthread_mutex_unlock(&philo.data->sim_mutex);
			return (FALSE);
		}
		pthread_mutex_unlock(&philo.data->sim_mutex);
		return (TRUE);
	}
	return (FALSE);
}

/**
 * is_full - Checks if if all philosophers eaten at lease n required times
 * @data: Pointer to the shared data structure
 */
static int	is_full(t_data *data)
{
	int	i;
	int	full;

	full = TRUE;
	if (data->required_meals == -1)
		return (FALSE);
	pthread_mutex_lock(&data->meal_mutex);
	i = 0;
	while (i < data->n_ph)
	{
		if (data->meals_eaten[i] < data->required_meals)
		{
			full = FALSE;
			break ;
		}
		i++;
	}
	pthread_mutex_unlock(&data->meal_mutex);
	return (full);
}

/**
 * monitor - Keeps track of the current starvation state of the philosophers
 * @arg: Address of the thread routine argument function
 * Return: NULL
 */
void	*monitor(void *arg)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)arg;
	i = 0;
	while (1)
	{
		i = 0;
		if (is_full(philo[0].data) == TRUE)
			return (sim_stop(philo[0].data), NULL);
		while (i < philo[0].data->n_ph)
		{
			better_usleep(1, philo[0].data);
			if (starved(philo[i]) == TRUE)
				return (sim_stop(philo[0].data), NULL);
			i++;
		}
	}
	return (NULL);
}

/**
 * handle_monitoring - Start the monitoring thread
 * @th: The thread
 * @philos: An array of t_philo structs
 */
void	handle_monitoring(pthread_t *th, t_philo **philos)
{
	pthread_create(th, NULL, monitor, *philos);
}
