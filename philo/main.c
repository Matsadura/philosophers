/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaoui <zzaoui@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 09:22:37 by zzaoui            #+#    #+#             */
/*   Updated: 2025/03/11 17:46:55 by zzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		pthread_mutex_lock(&data.sim_mutex);
		data.sim_stop = TRUE;
		pthread_mutex_unlock(&data.sim_mutex);
		i = -1;
		while(++i < data.n_ph)
			pthread_join(th[i], NULL);
		cleanup(th, philos, data);
	}
	else
		printf("Error\n");
	return (EXIT_SUCCESS);
}
