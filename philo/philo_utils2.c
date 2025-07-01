/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaoui <zzaoui@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 04:00:20 by zzaoui            #+#    #+#             */
/*   Updated: 2025/06/30 04:00:22 by zzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * get_for_order - Sets the pick order of the forks
 */
static void	get_fork_order(int *first, int *second, int left, int right)
{
	if (left < right)
	{
		*first = left;
		*second = right;
	}
	else
	{
		*first = right;
		*second = left;
	}
}

/**
 * handle_one_philo - handles the case of a sole philosopher
 */
static int	handle_one_philo(t_philo philo, int fork_index)
{
	pthread_mutex_lock(&philo.data->forks[fork_index]);
	print_state(philo, FORK_UP);
	usleep(philo.data->time_to_die);
	pthread_mutex_unlock(&philo.data->forks[fork_index]);
	return (FALSE);
}

/**
 * pick_forks - Puts back the previously picked forks
 * @philo: The philosopher to pick up the forks
 */
int	pick_forks(t_philo philo)
{
	int	left;
	int	right;
	int	first;
	int	second;

	left = philo.id - 1;
	right = philo.id % philo.data->n_ph;
	if (philo.data->n_ph == 1)
		return (handle_one_philo(philo, right));
	get_fork_order(&first, &second, left, right);
	pthread_mutex_lock(&philo.data->forks[first]);
	print_state(philo, FORK_UP);
	pthread_mutex_lock(&philo.data->forks[second]);
	print_state(philo, FORK_UP);
	return (TRUE);
}
