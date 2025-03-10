/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaoui <zzaoui@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 09:20:24 by zzaoui            #+#    #+#             */
/*   Updated: 2025/03/10 09:20:29 by zzaoui           ###   ########.fr       */
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
	int		n_ph;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		required_meals;
}			t_data;

typedef struct s_philo
{
	int		id;
	t_data	*data;
}			t_philo;

/* */
int			parse_args(int ac, char **av, t_data *data);

/* Helper functions */
int			ft_isdigit(int c);
int			ft_atoi(const char *str);
long		ft_atol(const char *str);

#endif /* PHILO_H */
