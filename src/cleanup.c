/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diade-so <diade-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 18:30:40 by diade-so          #+#    #+#             */
/*   Updated: 2025/08/19 18:36:08 by diade-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Free allocated resources and print a message.
 *
 * Frees the philosophers array, destroys fork mutexes, and
 * destroys the print_lock mutex.
 *
 * @param sim Pointer to the simulation structure.
 * @param msg Optional message to print before cleanup (can be NULL).
 */
void	cleanup(t_sim *sim, const char *msg)
{
	int	i;

	if (!sim)
		return;
	if (msg)
		printf("%s\n", msg);
	if (sim->philos)
		free(sim->philos);
	if (sim->forks)
	{
		i = 0;
		while (i < sim->args.num_philos)
		{
			pthread_mutex_destroy(&sim->forks[i]);
			i++;
		}
		free(sim->forks);
	}
	pthread_mutex_destroy(&sim->print_lock);
	pthread_mutex_destroy(&sim->stop_lock);
}

/**
 * @brief Destroy all mutexes used in the simulation.
 *
 * Cleans up stop_lock, print_lock, all fork mutexes, and
 * each philosopher's meal_lock to prevent resource leaks.
 *
 * @param sim Pointer to the simulation structure.
 */
void destroy_mutexes(t_sim *sim)
{
	int i;

	if (!sim)
		return;
	pthread_mutex_destroy(&sim->stop_lock);
	pthread_mutex_destroy(&sim->print_lock);
	i = 0;
	while (i < sim->args.num_philos)
	{
		pthread_mutex_destroy(&sim->philos[i].meal_lock);
		i++;
	}
	if (sim->forks)
	{
		i = 0;
		while (i < sim->args.num_philos)
		{
			pthread_mutex_destroy(&sim->forks[i]);
			i++;
		}
	}
}

