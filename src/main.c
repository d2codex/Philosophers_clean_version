/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diade-so <diade-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 15:22:21 by diade-so          #+#    #+#             */
/*   Updated: 2025/08/19 23:00:58 by diade-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Initializes and starts the philosopher simulation.
 *
 * Sets synchronized start times, spawns philosopher threads,
 * and launches the monitor thread.
 *
 * @param sim Simulation struct containing philosophers and shared data.
 */
void	start_simulation(t_sim *sim)
{
	long	t_start;
	int		i;

	if (!sim || !sim->args.num_philos)
		return ;
	t_start = get_time_ms() + 50;
	i = 0;
	while (i < sim->args.num_philos)
	{
		sim->philos[i].last_meal_time = t_start;
		i++;
	}
	i = 0;
	while (i < sim->args.num_philos)
	{
		pthread_create(&sim->philos[i].thread, NULL,
			(void *)philo_routine, &sim->philos[i]);
		i++;
	}
	pthread_create(&sim->monitor_thread, NULL, monitor, sim);
}

/**
 * @brief Stops the simulation and cleans up all resources.
 *
 * This function signals that the simulation has ended, waits for all
 * philosopher threads and the monitor thread to finish, destroys all
 * mutexes associated with forks, and frees dynamically allocated memory.
 *
 * @param sim Pointer to the simulation struct containing philosophers and forks.
 */
void	stop_simulation(t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->args.num_philos)
	{
		pthread_join(sim->philos[i].thread, NULL);
		i++;
	}
	pthread_join(sim->monitor_thread, NULL);
	i = 0;
	while (i < sim->args.num_philos)
	{
		pthread_mutex_destroy(&sim->forks[i]);
		i++;
	}
	free(sim->philos);
	free(sim->forks);
}


int	main(int ac, char **av)
{
	t_sim sim;

	if (init_args(ac, av, &sim.args) != 0)
		return (1);
	if (sim.args.num_philos == 1)
	{
		handle_one_philo(&sim);
		return 0;
	}	
	if (init_forks(&sim) != 0)
		return (cleanup(&sim, "Failed to initialize forks"), 1);

	if (init_philos(&sim) != 0)
		return (cleanup(&sim, "Failed to initialize philosophers"), 1);
	init_mutexes(&sim);
	start_simulation(&sim);
	stop_simulation(&sim);
	cleanup(&sim, "Simulation ended");	
	return (0);
}

