/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaoui <zzaoui@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 09:22:37 by zzaoui            #+#    #+#             */
/*   Updated: 2025/03/13 10:30:19 by zzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * init - Initializes all values
 * @philo: Pointer to an array of t_philo structs
 * @data: Pointer to shared data struct
 * Return: True if no malloc fails, False otherwise
 */
static int	init(t_philo **philos, t_data *data)
{
	int	i;

	*philos = malloc(data->n_ph * sizeof(t_philo));
	data->forks = malloc(data->n_ph * sizeof(pthread_mutex_t));
	data->last_time_meals = malloc(data->n_ph * sizeof(long long));
	data->meals_eaten = malloc(data->n_ph * sizeof(int));
	if (data->forks == NULL || data->last_time_meals == NULL
		|| data->meals_eaten == NULL)
		return (FALSE);
	pthread_mutex_init(&data->sim_mutex, NULL);
	pthread_mutex_init(&data->meal_mutex, NULL);
	pthread_mutex_init(&data->print_mutex, NULL);
	data->start_time = current_time_milis();
	data->sim_stop = FALSE;
	i = -1;
	while (++i < data->n_ph)
		pthread_mutex_init(&data->forks[i], NULL);
	i = -1;
	while (++i < data->n_ph)
		data->meals_eaten[i] = 0;
	i = -1;
	while (++i < data->n_ph)
		data->last_time_meals[i] = data->start_time;
	return (TRUE);
}

static void cleanup(pthread_t *th, t_philo *philos, t_data data)
{
	int	i;

	pthread_mutex_destroy(&data.meal_mutex);
	pthread_mutex_destroy(&data.sim_mutex);
	pthread_mutex_destroy(&data.print_mutex);
	i = -1;
	while(++i < data.n_ph)
		pthread_mutex_destroy(&data.forks[i]);
	free(philos);
	free(data.forks);
	free(data.last_time_meals);
	free(data.meals_eaten);
	free(th);
}

/**
 * main - The program's entry point
 * @ac: argument count
 * @av: argument vector
 * Return: 0 if success, 1 otherwise
 */
int	main(int ac, char **av)
{
	t_data	data;
	t_philo *philos;
	pthread_t *th;
	pthread_t th_monitor;
	int	i;

	if (ac == 5 || ac == 6)
	{
		if (parse_args(ac, av, &data) == -1)
			return (printf("Error\n"), EXIT_FAILURE);
		init(&philos, &data);
		create_philos(&th, &philos, &data);
		handle_monitoring(&th_monitor, &philos);
		pthread_join(th_monitor, NULL);
		i = -1;
		while(++i < data.n_ph)
			pthread_join(th[i], NULL);
		cleanup(th, philos, data);
	}
	else
		printf("Error\n");
	return (EXIT_SUCCESS);
}
