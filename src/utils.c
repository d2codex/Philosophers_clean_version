/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diade-so <diade-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 15:25:31 by diade-so          #+#    #+#             */
/*   Updated: 2025/08/19 17:23:39 by diade-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Returns the length of a null-terminated string.
 *
 * @param str Pointer to the string.
 * @return int Number of characters in the string (excluding null terminator).
 */
int	ft_strlen(const char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

/**
 * @brief Convert a digit-only string to a positive long.
 *
 * Validates that the string contains only digits and checks for overflow.
 *
 * @param str Input string (must not be NULL or empty).
 * @param out Pointer to store the result.
 * @return 1 on success, 0 on invalid input or overflow.
 */
int	ft_atol(const char *str, long *out)
{
	long	result;

	result = 0;
	if (!str || !out || *str == '\0')
		return (0);
	while (*str)
	{
		if(*str < '0' || *str > '9')
			return (0);
		if (result > (LONG_MAX -(*str - '0')) / 10)
			return (0);
		result = result * 10 + (*str - '0');
		str++;
	}
	*out = result;
	return (1);
}

/**
 * @brief Convert a digit-only string to a positive int.
 *
 * Validates digits and checks for overflow.
 *
 * @param str Input string (must not be NULL or empty).
 * @param out Pointer to store the result.
 * @return 1 on success, 0 on invalid input or overflow.
 */
int	ft_atoi(const char *str, int *out)
{
	long	result;

	result = 0;
	if (!str || !out || *str == '\0')
		return (0);
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		result = result * 10 + (*str - '0');
		if (result > INT_MAX)
			return (0);
		str++;
	}
	*out = result;
	return (1);
}

/**
 * @brief Prints the correct usage and argument requirements for the program.
 *
 * Lists each expected argument, its valid range, and whether it is optional.
 */
void	print_usage(void)
{
	printf("Usage: ./philo <number_of_philos> <time_to_die> " 
			"<time_to_eat> <time_to_sleep> [meal_goal]\n");
	printf("Arguments:\n");
	printf("  number_of_philos  : >= 1\n");
	printf("  time_to_die       : > 0 (ms)\n");
	printf("  time_to_eat       : > 0 (ms)\n");
	printf("  time_to_sleep     : >= 0 (ms)\n");
	printf("  meal_goal         : >= 1 (optional, default = no limit)\n");
}
