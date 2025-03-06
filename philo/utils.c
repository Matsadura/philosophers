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