#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <pthread.h>
# include <sys/types.h>
# include <sys/time.h>

# define TRUE 1
# define FALSE 0

# define STDERR 2

typedef struct	s_data
{
	int	n_ph;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	required_meals;
} t_data;

/* */
int	parse_args(int ac, char **av, t_data *data);

/* Helper functions */
int	ft_isdigit(int c);
int ft_atoi(const char *str);

#endif /* PHILO_H */