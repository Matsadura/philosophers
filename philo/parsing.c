#include "philo.h"

/**
 * is_numerical - Checks if all elements are numerical
 * @args: An array of arrays representing list of arguments
 */
static int	is_numerical(char **args)
{
	int	i;
	int	j;

	i = 1;
	while (args[i] != NULL)
	{
		j = 0;
		if ((args[i][j] == '-' || args[i][j] == '+')
		&& (args[i][j + 1] != '\0'
			&& ft_isdigit((int)args[i][j + 1]) == TRUE))
			j++;
		while (args[i][j] != '\0')
		{
			if (ft_isdigit((int)args[i][j]) == FALSE)
			{
				printf("the digit: %c\n", args[i][j]);
				printf("Error\n");
				return (FALSE);
			}
			j++;
		}
		i++;
	}
	return (TRUE);
}

/**
 * 
 */
int parse_args(int ac, char **av, t_data *data)
{

	if (is_numerical(av) == FALSE)
		return (-1);
	data->n_ph = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 5)
		data->required_meals = -1;
	else
		data->required_meals = ft_atoi(av[5]);
	return (0);
}