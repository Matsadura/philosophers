/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaoui <zzaoui@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 09:37:13 by zzaoui            #+#    #+#             */
/*   Updated: 2025/03/10 11:27:32 by zzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * 
 */
void    init(t_philo **philos, t_data *data)
{
    *philos = malloc(data->n_ph * sizeof(t_philo));
    data->forks = malloc(data->n_ph * sizeof(pthread_mutex_t));
    data->last_time_meals = malloc(data->n_ph * sizeof(long long));
    data->meals_eaten = malloc(data->n_ph * sizeof(int));

    /** to redo */
    data->start_time = current_time_milis();
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
        pthread_create(&((*th)[i]), NULL, test_func, &((*philos)[i]));
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
