/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diade-so <diade-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 15:22:21 by diade-so          #+#    #+#             */
/*   Updated: 2025/08/25 16:37:12 by diade-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Starts and manages the philosopher simulation.
 *
 * Initializes start time, launches philosopher and monitor threads,
 * and blocks until all threads complete.
 *
 * @param sim Pointer to the simulation context.
 */
void	run_simulation(t_sim *sim)
{
	int		i;

	if (!sim || !sim->args.num_philos)
		return ;
	sim->start_time = get_time_ms() + 50;
	i = 0;
	while (i < sim->args.num_philos)
		sim->philos[i++].last_meal_time = sim->start_time;
	i = 0;
	while (i < sim->args.num_philos)
	{
		pthread_create(&sim->philos[i].thread, NULL,
			(void *)philo_routine, &sim->philos[i]);
		i++;
	}
	pthread_create(&sim->monitor_thread, NULL, monitor, sim);
	i = 0;
	while (i < sim->args.num_philos)
		pthread_join(sim->philos[i++].thread, NULL);
	pthread_join(sim->monitor_thread, NULL);
}

int	main(int ac, char **av)
{
	t_sim	sim;

	if (init_args(ac, av, &sim.args) != 0)
		return (1);
	if (sim.args.num_philos == 1)
	{
		handle_one_philo(&sim);
		return (0);
	}
	if (init_sim(&sim) != 0)
		return (destroy_sim(&sim, "Failed to initialize simulation"), 1);
	if (init_forks(&sim) != 0)
		return (destroy_sim(&sim, "Failed to initialize forks"), 1);
	if (init_philos(&sim) != 0)
		return (destroy_sim(&sim, "Failed to initialize philosophers"), 1);
	run_simulation(&sim);
	destroy_sim(&sim, NULL);
	return (0);
}
