/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaoui <zzaoui@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 09:37:13 by zzaoui            #+#    #+#             */
/*   Updated: 2025/03/12 13:54:32 by zzaoui           ###   ########.fr       */
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
    data->sim_stop = FALSE;
	i = -1;
	while(++i < data->n_ph)
		pthread_mutex_init(&data->forks[i], NULL);
	i = -1;
	while(++i < data->n_ph)
		data->meals_eaten[i] = 0;	
    i = -1;
	while(++i < data->n_ph)
		data->last_time_meals[i] = data->start_time;	
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
        pthread_mutex_lock(&philo->data->sim_mutex);
        if (philo->data->sim_stop == TRUE)
        {
            pthread_mutex_unlock(&philo->data->sim_mutex);
            break;
        }
        pthread_mutex_unlock(&philo->data->sim_mutex);
        print_state(*philo, THINKING);
        pick_forks(*philo);
        eat(philo);
        //printf("STOP?: %d\n", philo->data->sim_stop);
        put_forks(*philo);
        print_state(*philo, SLEEPING);
        better_usleep(philo->data->time_to_sleep, philo->data);
    }
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
        pthread_create(&((*th)[i]), NULL, philosopher, &((*philos)[i]));
        usleep(100);
        i++;
    }
    
	/* TO RMV*/
	//i = 0;
 //   while (i < data->n_ph)
 //   {
 //       pthread_join((*th)[i], NULL);
 //       i++;
 //  0}
}
