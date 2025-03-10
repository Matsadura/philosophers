/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaoui <zzaoui@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 09:22:37 by zzaoui            #+#    #+#             */
/*   Updated: 2025/03/10 11:19:10 by zzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void cleanup(pthread_t *th, t_philo *philos, t_data data)
{
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

	if (ac == 5 || ac == 6)
	{
		if (parse_args(ac, av, &data) == -1)
			return (printf("Error\n"), EXIT_FAILURE);
		init(&philos, &data);
        printf("Sim start time: %lld\n", data.start_time);
        create_philos(&th, &philos, &data);
        cleanup(th, philos, data);
	}
	else
		printf("Error\n");
	return (EXIT_SUCCESS);
}
