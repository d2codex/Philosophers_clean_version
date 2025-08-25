/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diade-so <diade-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 22:52:08 by diade-so          #+#    #+#             */
/*   Updated: 2025/08/25 16:39:20 by diade-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Checks if any philosopher has starved.
 *
 * Iterates through all philosophers and compares the time since their last meal
 * to time_til_death. Returns a pointer to the first philosopher that exceeded
 * the limit, or NULL if none have starved.
 *
 * @param sim Pointer to the simulation structure containing philosophers and 
 * timing info.
 * 
 * @return Pointer to the starving philosopher, or NULL if all are alive.
 */
t_philo	*check_starvation(t_sim *sim)
{
	long	now;
	int		i;

	now = get_sim_time(sim);
	i = 0;
	while (i < sim->args.num_philos)
	{
		pthread_mutex_lock(&sim->philos[i].meal_lock);
		if (now - sim->philos[i].last_meal_time
			> sim->args.time_to_die)
		{
			pthread_mutex_unlock(&sim->philos[i].meal_lock);
			return (&sim->philos[i]);
		}
		pthread_mutex_unlock(&sim->philos[i].meal_lock);
		i++;
	}
	return (NULL);
}

/**
 * @brief Checks if all philosophers have reached their meal goal.
 *
 * Loops through all philosophers and verifies if each has eaten at least
 * meal_goal times. If any philosopher hasn't, it returns 0. Otherwise,
 * returns 1.
 *
 * @param sim Pointer to the simulation structure containing philosophers and
 * meal goal.
 * 
 * @return 1 if all have met the goal, 0 otherwise.
 */
int	check_meal_goal(t_sim *sim)
{
	int	i;

	if (sim->args.meal_goal <= 0)
		return (0);
	i = 0;
	while (i < sim->args.num_philos)
	{
		pthread_mutex_lock(&sim->philos[i].meal_lock);
		if (sim->philos[i].meals_eaten < sim->args.meal_goal)
		{
			pthread_mutex_unlock(&sim->philos[i].meal_lock);
			return (0);
		}
		pthread_mutex_unlock(&sim->philos[i].meal_lock);
		i++;
	}
	return (1);
}

/**
 * @brief Continuously monitors philosophers for death or meal completion.
 *
 * This function runs in its own thread. It repeatedly checks if any philosopher
 * has starved using check_starvation(), or if all have met their meal goals
 * using check_meal_goal(). If a philosopher dies, it prints the death message
 * and stops the simulation. If the meal goal is reached, it stops the
 * simulation.
 *
 * @param arg Pointer to t_sim containing simulation info and philosophers array.
 * @return Always returns NULL (thread exit).
 */
void	*monitor(void *arg)
{
	t_sim	*sim;
	t_philo	*dead;

	sim = (t_sim *)arg;
	wait_for_start(sim);
	while (!is_simulation_stopped(sim))
	{
		dead = check_starvation(sim);
		if (dead)
		{
			print_display_msg(dead, DIED);
			set_simulation_stopped(sim, true);
			return (NULL);
		}
		if (check_meal_goal(sim))
		{
			set_simulation_stopped(sim, true);
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}

/**
 * @brief Check if the simulation has been stopped.
 *
 * This function reads the simulation_stopped flag
 * using the stop_lock mutex to avoid race conditions.
 *
 * @param sim Pointer to the simulation structure.
 * @return true if the simulation is stopped, false otherwise.
 */
bool	is_simulation_stopped(t_sim *sim)
{
	bool	stopped;

	pthread_mutex_lock(&sim->stop_lock);
	stopped = sim->sim_stopped;
	pthread_mutex_unlock(&sim->stop_lock);
	return (stopped);
}

/**
 * @brief Sets the simulation stopped flag.
 *
 * This function updates the simulation_stopped flag
 * while holding the stop_lock mutex to prevent race conditions.
 *
 * @param sim   Pointer to the simulation structure.
 * @param value Boolean value to set the simulation_stopped flag.
 */
void	set_simulation_stopped(t_sim *sim, bool value)
{
	pthread_mutex_lock(&sim->stop_lock);
	sim->sim_stopped = value;
	pthread_mutex_unlock(&sim->stop_lock);
}
