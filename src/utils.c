/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diade-so <diade-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 15:25:31 by diade-so          #+#    #+#             */
/*   Updated: 2025/08/25 17:35:36 by diade-so         ###   ########.fr       */
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
		if (*str < '0' || *str > '9')
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
 * @brief Validate and parse philosopher arguments.
 *
 * Converts input strings to integers/longs, checks allowed ranges,
 * and assigns the values to the args struct.
 *
 * @param ac Argument count.
 * @param av Argument vector.
 * @param args Pointer to args struct to fill.
 * @return 0 if valid, non-zero on error.
 */
int	validate_args(int ac, char **av, t_args *args)
{
	int	error_found;

	error_found = 0;
	if (!ft_atoi(av[1], &args->num_philos) || args->num_philos <= 0
		|| args->num_philos > 200)
		error_found |= error_return("Philo number must be between 1 and 200\n");
	if (!ft_atol(av[2], &args->time_to_die) || args->time_to_die <= 0
		|| args->time_to_die > 60000)
		error_found |= error_return("Time to die must be between 1 and 60000\n");
	if (!ft_atol(av[3], &args->time_to_eat) || args->time_to_eat <= 0
		|| args->time_to_eat > 60000)
		error_found |= error_return("Time to eat must be between 1 and 60000\n");
	if (!ft_atol(av[4], &args->time_to_sleep) || args->time_to_sleep <= 0
		|| args->time_to_sleep > 60000)
		error_found |= error_return("Time to sleep must be 1 to 60000\n");
	if (ac == 6)
	{
		if (!ft_atoi(av[5], &args->meal_goal) || args->meal_goal <= 0
			|| args->meal_goal > 500)
			error_found |= error_return("Meal goal must be between 1 and 500\n");
	}
	else
		args->meal_goal = -1;
	return (error_found);
}
