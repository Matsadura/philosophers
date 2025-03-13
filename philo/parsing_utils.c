/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaoui <zzaoui@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 09:20:40 by zzaoui            #+#    #+#             */
/*   Updated: 2025/03/13 12:34:54 by zzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * ft_isdigit - Checks for a digit (0 through 9)
 * @c: The element to check
 * Return: 1 if true, 0 otherwise
 */
int	ft_isdigit(int c)
{
	if ('0' <= c && c <= '9')
		return (1);
	return (0);
}

/**
 * ft_atoi - convert ASCII string to integer
 * @str: the string to convert
 * Return: the result integer
 */
int	ft_atoi(const char *str)
{
	int	i;
	int	result;
	int	sign;

	sign = 1;
	result = 0;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-')
	{
		sign *= -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (ft_isdigit(str[i]))
	{
		result = result * 10 + str[i] - 48;
		if (result < INT_MIN || result > INT_MAX)
			return ((size_t)INT_MAX + 1);
		i++;
	}
	return (result * sign);
}

/**
 * ft_atol - convert ASCII string to long integer
 * @str: the string to convert
 * Return: the result long integer
 */
long	ft_atol(const char *str)
{
	long (i), (result), (sign);
	sign = 1;
	result = 0;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-')
	{
		sign *= -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (ft_isdigit(str[i]))
	{
		result = result * 10 + str[i] - 48;
		result *= sign;
		if (result < INT_MIN || result > INT_MAX)
			return (2147483648);
		result *= sign;
		i++;
	}
	return (result * sign);
}
