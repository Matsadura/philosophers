/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaoui <zzaoui@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 15:25:12 by zzaoui            #+#    #+#             */
/*   Updated: 2025/06/30 15:25:15 by zzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * free_init_allocs - Frees all allocated memory during initialization
 * @philos: Pointer to the philosopher array
 * @data: Pointer to shared data struct
 */
static void	free_init_allocs(t_philo **philos, t_data *data)
{
	if (*philos)
		free(*philos);
	if (data->forks)
		free(data->forks);
	if (data->last_time_meals)
		free(data->last_time_meals);
	if (data->meals_eaten)
		free(data->meals_eaten);
}

/**
 * init_mutexes - Initializes all mutexes used in the simulation
 * @data: Pointer to shared data struct
 */
static void	init_mutexes(t_data *data)
{
	int	i;

	pthread_mutex_init(&data->sim_mutex, NULL);
	pthread_mutex_init(&data->meal_mutex, NULL);
	pthread_mutex_init(&data->print_mutex, NULL);
	i = -1;
	while (++i < data->n_ph)
		pthread_mutex_init(&data->forks[i], NULL);
}

/**
 * init_arrays - Initializes the meals_eaten and last_time_meals arrays
 * @data: Pointer to shared data struct
 */
static void	init_arrays(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->n_ph)
		data->meals_eaten[i] = 0;
	i = -1;
	while (++i < data->n_ph)
		data->last_time_meals[i] = data->start_time;
}

/**
 * init - Initializes all values
 * @philo: Pointer to an array of t_philo structs
 * @data: Pointer to shared data struct
 * Return: True if no malloc fails, False otherwise
 */
int	init(t_philo **philos, t_data *data)
{
	*philos = malloc(data->n_ph * sizeof(t_philo));
	data->forks = malloc(data->n_ph * sizeof(pthread_mutex_t));
	data->last_time_meals = malloc(data->n_ph * sizeof(long long));
	data->meals_eaten = malloc(data->n_ph * sizeof(int));
	if (*philos == NULL || data->forks == NULL || data->last_time_meals == NULL
		|| data->meals_eaten == NULL)
	{
		free_init_allocs(philos, data);
		return (FALSE);
	}
	init_mutexes(data);
	data->start_time = current_time_milis();
	data->sim_stop = FALSE;
	init_arrays(data);
	return (TRUE);
}

/**
 * cleanup - Cleans up all allocated resources
 * @th: Pointer to the thread array
 * @philos: Pointer to the philosopher array
 * @data: Shared data struct containing mutexes and other data
 */
void	cleanup(pthread_t *th, t_philo *philos, t_data data)
{
	int	i;

	i = -1;
	while (++i < data.n_ph)
		pthread_mutex_destroy(&data.forks[i]);
	pthread_mutex_destroy(&data.meal_mutex);
	pthread_mutex_destroy(&data.sim_mutex);
	pthread_mutex_destroy(&data.print_mutex);
	if (philos)
		free(philos);
	if (data.forks)
		free(data.forks);
	if (data.last_time_meals)
		free(data.last_time_meals);
	if (data.meals_eaten)
		free(data.meals_eaten);
	if (th)
		free(th);
}
