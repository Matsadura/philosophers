/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaoui <zzaoui@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 10:39:21 by zzaoui            #+#    #+#             */
/*   Updated: 2025/03/11 17:45:10 by zzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * starved - Check if a philospher has starved to death
 * @philo: The philosopher to check
 * Return: TRUE if starved, FALSE otherwise
 */
static int	starved(t_philo philo)
{
	int	meals;
	int	last_meal;

	pthread_mutex_lock(&philo.data->meal_mutex);
	meals = philo.data->meals_eaten[philo.id - 1];
	last_meal = philo.data->last_time_meals[philo.id- 1];
	pthread_mutex_unlock(&philo.data->meal_mutex);
	if (meals == 0)
	{
		if ((current_time_milis()
				- philo.data->start_time) > philo.data->time_to_die)
		{
			print_state(philo, DIED);
			return (TRUE);
		}
	}
	else if (meals != 0)
	{
		if ((current_time_milis() - last_meal) > philo.data->time_to_die)
		{
			print_state(philo, DIED);
			return (TRUE);
		}
	}
	return (FALSE);
}

/**
 * 
 */

/**
 * monitor - Keeps track of the current starvation state of the philosophers
 * @arg: Address of the thread routine argument function
 * Return: NULL
 */
void	*monitor(void *arg)
{
	t_philo	*philo;
	int	i;

	philo = (t_philo *)arg;
	i = 0;
	while (1)
	{
		i = 0;
		while (i < philo[0].data->n_ph)
		{
			if (starved(philo[i]) == TRUE)
			{
				pthread_mutex_lock(&philo[i].data->sim_mutex);
				philo[i].data->sim_stop = TRUE;
				pthread_mutex_unlock(&philo[i].data->sim_mutex);
				return (NULL);
			}
			i++;
		}
		better_usleep(1);
	}
	return (NULL);
}

/**
 * handle_monitoring
 */
void    handle_monitoring(pthread_t *th, t_philo **philos)
{
	pthread_create(th, NULL, monitor, *philos);
}