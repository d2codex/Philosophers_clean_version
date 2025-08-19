/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diade-so <diade-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 16:20:22 by diade-so          #+#    #+#             */
/*   Updated: 2025/08/19 21:34:36 by diade-so         ###   ########.fr       */
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

/**
 * @brief Allocates and initializes the fork mutexes.
 * 
 * @param sim Pointer to the simulation struct containing forks.
 * @return int 0 on success, 1 on failure
 */
int	init_forks(t_sim *sim)
{
	int	i;

	sim->forks = malloc(sizeof(pthread_mutex_t) * sim->args.num_philos);
	if (!sim->forks)
		return (error_return("Failed to malloc for forks\n"));

	i = 0;
	while (i < sim->args.num_philos)
	{
		if (pthread_mutex_init(&sim->forks[i], NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&sim->forks[i]);
			free(sim->forks);
			sim->forks = NULL;
			return (error_return("Mutex init failed\n"));
		}
		i++;
	}
	return 0;
}

/**
 * @brief Allocates and initializes philosopher structs.
 * 
 * @param sim Pointer to the simulation struct containing philos and forks.
 * @return int 0 on success, 1 on failure
 */
int	init_philos(t_sim *sim)
{
	int	i;

	sim->philos = malloc(sizeof(t_philo) * sim->args.num_philos);
	if (!sim->philos)
		return (error_return("Failed to malloc for philos\n"));

	i = 0;
	while (i < sim->args.num_philos)
	{
		sim->philos[i].id = i + 1;
		sim->philos[i].last_meal_time = 0;
		sim->philos[i].start_time = 0;
		sim->philos[i].meals_eaten = 0;
		sim->philos[i].fork1 = &sim->forks[i];
		sim->philos[i].fork2 = &sim->forks[(i + 1) % sim->args.num_philos];
		pthread_mutex_init(&sim->philos[i].meal_lock, NULL);
		i++;
	}
	return 0;
}

/**
 * @brief Initializes simulation-wide mutexes.
 * 
 * @param sim Pointer to simulation struct
 */
void	init_mutexes(t_sim *sim)
{
	int	i;

	pthread_mutex_init(&sim->print_lock, NULL);
	pthread_mutex_init(&sim->stop_lock, NULL);

	i = 0;
	while (i < sim->args.num_philos)
	{
		pthread_mutex_init(&sim->philos[i].meal_lock, NULL);
		i++;
	}
}