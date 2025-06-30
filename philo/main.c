/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaoui <zzaoui@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 09:22:37 by zzaoui            #+#    #+#             */
/*   Updated: 2025/05/15 00:23:18 by zzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * main - The program's entry point
 * @ac: argument count
 * @av: argument vector
 * Return: 0 if success, 1 otherwise
 */
int	main(int ac, char **av)
{
	t_data		data;
	t_philo		*philos;
	pthread_t	*th;
	pthread_t	th_monitor;
	int			i;

	if (ac == 5 || ac == 6)
	{
		if (parse_args(ac, av, &data) == -1)
			return (printf("Error\n"), EXIT_FAILURE);
		if (init(&philos, &data) == FALSE)
			return (printf("Error\n"), EXIT_FAILURE);
		create_philos(&th, &philos, &data);
		handle_monitoring(&th_monitor, &philos);
		pthread_join(th_monitor, NULL);
		i = -1;
		while (++i < data.n_ph)
			pthread_join(th[i], NULL);
		usleep(1000);
		cleanup(th, philos, data);
	}
	else
		printf("Error\n");
	return (EXIT_SUCCESS);
}
