/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diade-so <diade-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 16:20:22 by diade-so          #+#    #+#             */
/*   Updated: 2025/08/19 17:16:04 by diade-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Initializes t_args from program arguments.
 * 
 * Converts input strings to numbers and validates them.
 * Returns 1 if any argument is invalid, 0 on success.
 * 
 * @param ac Argument count (from main)
 * @param av Argument values (from main)
 * @param args Pointer to t_args struct to initialize
 * @return int 0 on success, 1 on error
 */
int	init_args(int ac, char **av, t_args *args)
{
	int	error_found;

	if (ac < 5 || ac > 6)
		return (error_return("Invalid number of arguments\n"),
			print_usage(), 1);
	error_found = 0;
	if (!ft_atoi(av[1], &args->num_philos) || args->num_philos <= 0)
		error_found |= error_return("Invalid number of philosophers\n");
	if (!ft_atol(av[2], &args->time_to_die) || args->time_to_die <= 0)
		error_found |= error_return("Invalid time to die\n");
	if (!ft_atol(av[3], &args->time_to_eat) || args->time_to_eat <= 0)
		error_found |= error_return("Invalid time to eat\n");
	if (!ft_atol(av[4], &args->time_to_sleep))
		error_found |= error_return("Invalid time to sleep\n");
	if (ac == 6)
	{
		if (!ft_atoi(av[5], &args->meal_goal))
			error_found |= error_return("Invalid meal goal\n");
	}
	else
		args->meal_goal = -1;
	if (error_found)
		return (print_usage(), 1);
	return (error_found);
}

