/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaoui <zzaoui@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 09:20:24 by zzaoui            #+#    #+#             */
/*   Updated: 2025/03/10 17:06:10 by zzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/types.h>
# include <unistd.h>

# define TRUE 1
# define FALSE 0

typedef struct s_data
{
	int				n_ph;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				required_meals;
	long long		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	sim_mutex;
	int				sim_stop;
	long long		*last_time_meals;
	int				*meals_eaten;
}					t_data;

typedef struct s_philo
{
	int				id;
	t_data			*data;
}					t_philo;

/* */
int					parse_args(int ac, char **av, t_data *data);

/* Helper functions */
int					ft_isdigit(int c);
int					ft_atoi(const char *str);
long				ft_atol(const char *str);

/* */
void    init(t_philo **philos, t_data *data);
long long   current_time_milis(void);
void    create_philos(pthread_t **th, t_philo **philos, t_data *data);
void    print_state(t_philo philo, char *msg);

/* Philosopher actions */
void    pick_forks(t_philo philo);
void	put_forks(t_philo philo);

#endif /* PHILO_H */
