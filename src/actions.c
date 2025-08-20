/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diade-so <diade-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 21:45:24 by diade-so          #+#    #+#             */
/*   Updated: 2025/08/20 19:58:43 by diade-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Locks both forks for the philosopher, lower number fork first.
 * @param philo Pointer to the philosopher structure.
 */
void	grab_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->fork1);
		print_display_msg(philo, GOT_FORK1);
		pthread_mutex_lock(philo->fork2);
		print_display_msg(philo, GOT_FORK2);
	}
	else
	{
		pthread_mutex_lock(philo->fork2);
		print_display_msg(philo, GOT_FORK2);
		pthread_mutex_lock(philo->fork1);
		print_display_msg(philo, GOT_FORK1);
	}
}

/**
 * @brief Philosopher starts eating, increments meal count,
 * sleeps for the eat duration, and releases forks.
 *
 * @param philo Pointer to the philosopher structure.
 */
void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal_time = get_sim_time(philo->sim);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_lock);
	print_display_msg(philo, EATING);
	smart_sleep(philo->sim, philo->sim->args.time_to_eat);
	pthread_mutex_unlock(philo->fork1);
	pthread_mutex_unlock(philo->fork2);
}

/**
 * @brief Philosopher sleeps for the configured time.
 * @param philo Pointer to the philosopher structure.
 */
void	slumber(t_philo *philo)
{
	print_display_msg(philo, SLEEPING);
	smart_sleep(philo->sim, philo->sim->args.time_to_sleep);
}

/**
 * @brief Philosopher thinks for a bit before trying to eat again.
 *
 * This helps avoid grabbing forks right after eating, giving others a chance
 * to eat first. The wait time is based on how long until the philosopher would
 * die, so they don’t risk starving. If there’s no safe time left, thinking is skipped.
 *
 * @param philo The philosopher.
 */
void	think(t_philo *philo)
{
	long	now;
	long	elapsed;
	long	time_left;

	now = get_sim_time(philo->sim);
	elapsed = now - philo->last_meal_time;
	time_left = philo->sim->args.time_to_die - elapsed;

	if (time_left > 0)
	{
		print_display_msg(philo, THINKING);
		smart_sleep(philo->sim, time_left);
	}
}
