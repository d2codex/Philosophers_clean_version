/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diade-so <diade-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 22:45:06 by diade-so          #+#    #+#             */
/*   Updated: 2025/08/25 16:41:07 by diade-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Main routine executed by each philosopher thread.
 *
 * Waits for the synchronized start, staggers even philosophers,
 * and loops through eating, sleeping, and thinking until the
 * simulation stops or the meal goal is reached.
 *
 * @param arg Pointer to the philosopher structure (cast from void*).
 * @return void* Required by pthreads.
 */
void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_for_start(philo->sim);
	if (philo->id % 2 == 0)
		smart_sleep(philo->sim, philo->sim->args.time_to_eat / 2);
	while (!is_simulation_stopped(philo->sim))
	{
		if (philo->sim->args.meal_goal > 0
			&& philo->meals_eaten >= philo->sim->args.meal_goal)
			break ;
		grab_forks(philo);
		eat(philo);
		slumber(philo);
		think(philo);
	}
	return (NULL);
}

/**
 * @brief Handles the single-philosopher edge case.
 *
 * In a simulation with only one philosopher, the philosopher cannot eat
 * because there is only one fork. This function prints the appropriate
 * messages for taking the fork and dying after time_til_death milliseconds.
 *
 * @param args Pointer to the simulation arguments structure (t_args).
 */

void	handle_one_philo(t_sim *sim)
{
	long	start;
	long	elapsed;

	start = get_time_ms();
	elapsed = get_time_ms() - start;
	printf("%ld 1 has taken a fork\n", elapsed);
	usleep(sim->args.time_to_die * 1000);
	printf("%ld 1 died\n", elapsed + sim->args.time_to_die);
}
