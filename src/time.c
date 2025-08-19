/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diade-so <diade-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 18:18:36 by diade-so          #+#    #+#             */
/*   Updated: 2025/08/19 23:05:05 by diade-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Get current time in milliseconds.
 * @return Current time in ms since Epoch.
 */
long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000L + tv.tv_usec / 1000L);
}

/**
 * @brief Returns the current simulation time in milliseconds.
 *
 * Calculates elapsed time since simulation start.
 *
 * @param sim Pointer to simulation structure.
 * @return long Elapsed time in milliseconds since start.
 */
long	get_sim_time(t_sim *sim)
{
	return (get_time_ms() - sim->start_time);
}

/**
 * @brief Sleeps for a specified duration unless the simulation stops.
 *
 * Checks sim->sim_stopped every 100µs to allow early exit.
 *
 * @param sim Pointer to simulation structure.
 * @param ms  Duration to sleep in milliseconds.
 */
void	smart_sleep(t_sim *sim, long ms)
{
	long	wake_up;

	wake_up = get_sim_time(sim) + ms;
	while (!sim->sim_stopped && get_sim_time(sim) < wake_up)
		usleep(100);
}

/**
 * @brief Busy-waits until the simulation start time is reached.
 *
 * Ensures all philosopher threads start at the same time.
 *
 * @param sim Pointer to simulation structure.
 */
void	wait_for_start(t_sim *sim)
{
	while (get_time_ms() < sim->start_time)
		usleep(100);
}
