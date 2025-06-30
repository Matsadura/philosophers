/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaoui <zzaoui@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 09:20:44 by zzaoui            #+#    #+#             */
/*   Updated: 2025/05/15 00:23:32 by zzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		if ((args[i][j] == '-' || args[i][j] == '+') && (args[i][j + 1] != '\0'
				&& ft_isdigit((int)args[i][j + 1]) == TRUE))
			j++;
		while (args[i][j] != '\0')
		{
			if (ft_isdigit((int)args[i][j]) == FALSE)
			{
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
 * safe_atoi - Checks for invalid returns from atoi
 * @str: The string to convert
 * Return: -1 on failure, otherwise the result
 */
static int	safe_atoi(const char *str)
{
	long	result;

	result = ft_atol(str);
	if (result > INT_MAX || result < 0)
		return (-1);
	return ((int)result);
}

/**
 * safe_assigner - Assigns a value to a variable
 * @key: The variable to assign to
 * @value: The value to assign
 * Return: 0 on success, otherwise -1
 */
static int	safe_assigner(int *key, char *value)
{
	*key = safe_atoi(value);
	if (*key == -1)
		return (-1);
	return (0);
}

/**
 * parse_args - Parses to command line arguments
 * @ac: Argument count
 * @av: Argument vector
 * @data: Pointer to the t_data struct
 * Return: 0 on success otherwise -1
 */
int	parse_args(int ac, char **av, t_data *data)
{
	if (is_numerical(av) == FALSE)
		return (-1);
	if (safe_assigner(&data->n_ph, av[1]) == -1)
		return (-1);
	if (safe_assigner(&data->time_to_die, av[2]) == -1)
		return (-1);
	if (safe_assigner(&data->time_to_eat, av[3]) == -1)
		return (-1);
	if (safe_assigner(&data->time_to_sleep, av[4]) == -1)
		return (-1);
	if (ac == 5)
		data->required_meals = -1;
	else
	{
		if (safe_assigner(&data->required_meals, av[5]) == -1)
			return (-1);
	}
	return (0);
}
