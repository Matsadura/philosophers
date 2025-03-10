/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaoui <zzaoui@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 09:37:13 by zzaoui            #+#    #+#             */
/*   Updated: 2025/03/10 17:05:09 by zzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * 
 */
void    init(t_philo **philos, t_data *data)
{
	int	i;

    *philos = malloc(data->n_ph * sizeof(t_philo));
    data->forks = malloc(data->n_ph * sizeof(pthread_mutex_t));
    data->last_time_meals = malloc(data->n_ph * sizeof(long long));
    data->meals_eaten = malloc(data->n_ph * sizeof(int));
	pthread_mutex_init(&data->sim_mutex, NULL);
	pthread_mutex_init(&data->meal_mutex, NULL);
	pthread_mutex_init(&data->print_mutex, NULL);
    data->start_time = current_time_milis();
	i = -1;
	while(++i < data->n_ph)
		pthread_mutex_init(&data->forks[i], NULL);
	i = -1;
	while(++i < data->n_ph)
		data->meals_eaten[i] = 0;	
}

/**
 * a testing routine
 */
void    *test_func(void *philo)
{
    t_philo *arg = (t_philo *)philo;
    printf("Philo id: %d\n", arg->id);
    return (NULL);
}

/**
 * 
 */
void	*philosopher(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		print_state(*philo, " is thinking\n");
		pick_forks(*philo);
		put_forks(*philo);
		usleep(500);
	}
}

/**
 * create_philos
 */
void    create_philos(pthread_t **th, t_philo **philos, t_data *data)
{
    int i;

    *th = malloc(data->n_ph * sizeof(pthread_t));
    i = 0;
    while (i < data->n_ph)
    {
        (*philos)[i].id = i + 1;
        (*philos)[i].data = data;
        //pthread_create(&((*th)[i]), NULL, test_func, &((*philos)[i]));
        pthread_create(&((*th)[i]), NULL, philosopher, &((*philos)[i]));
		print_state((*philos)[i], "is alive\n"); // to rmv
        i++;
    }
    
	/* TO RMV*/
	i = 0;
    while (i < data->n_ph)
    {
        pthread_join((*th)[i], NULL);
        i++;
    }
}
