/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaoui <zzaoui@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 12:41:00 by zzaoui            #+#    #+#             */
/*   Updated: 2025/05/15 00:23:53 by zzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * print_state - Prints the current philosopher state
 * @philo: The concerned philosopher
 * @msg: The message to print
 */
void	print_state(t_philo philo, char *msg)
{
	long long	current_time;

	current_time = current_time_milis() - philo.data->start_time;
	pthread_mutex_lock(&philo.data->print_mutex);
	pthread_mutex_lock(&philo.data->sim_mutex);
	if (philo.data->sim_stop == TRUE)
	{
		pthread_mutex_unlock(&philo.data->sim_mutex);
		pthread_mutex_unlock(&philo.data->print_mutex);
		return ;
	}
	pthread_mutex_unlock(&philo.data->sim_mutex);
	printf("%lld %d %s", current_time, philo.id, msg);
	pthread_mutex_unlock(&philo.data->print_mutex);
}

/**
 * put_forks - Puts back the previously picked forks
 * @philo: The philosopher to put down the forks
 */
void	put_forks(t_philo philo)
{
	int	left;
	int	right;
	int	first;
	int	second;

	if (philo.data->n_ph == 1)
		return ;
	left = philo.id - 1;
	right = philo.id % philo.data->n_ph;
	if (left < right)
	{
		first = left;
		second = right;
	}
	else
	{
		first = right;
		second = left;
	}
	pthread_mutex_unlock(&philo.data->forks[first]);
	pthread_mutex_unlock(&philo.data->forks[second]);
}

/**
 * eat - Philosopher eating state
 * @philo: The hungry philosopher
 */
void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->meal_mutex);
	philo->data->last_time_meals[philo->id - 1] = current_time_milis();
	if (philo->data->required_meals != -1)
		philo->data->meals_eaten[philo->id - 1]++;
	pthread_mutex_unlock(&philo->data->meal_mutex);
	print_state(*philo, EATING);
	better_usleep(philo->data->time_to_eat, philo->data);
}
