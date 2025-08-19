/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diade-so <diade-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 22:35:42 by diade-so          #+#    #+#             */
/*   Updated: 2025/08/19 22:41:30 by diade-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Prints the correct usage and argument requirements for the program.
 *
 * Lists each expected argument, its valid range, and whether it is optional.
 */
void	print_usage(void)
{
	printf("Usage: ./philo <number_of_philos> <time_to_die> " 
			"<time_to_eat> <time_to_sleep> [meal_goal]\n");
	printf("Arguments:\n");
	printf("  number_of_philos  : >= 1\n");
	printf("  time_to_die       : > 0 (ms)\n");
	printf("  time_to_eat       : > 0 (ms)\n");
	printf("  time_to_sleep     : >= 0 (ms)\n");
	printf("  meal_goal         : >= 1 (optional, default = no limit)\n");
}

/**
 * @brief Safely prints a philosopher's action with timestamp.
 *
 * This function locks the shared print mutex to prevent data races.
 * If the action is DIED, it is printed immediately and the simulation
 * is marked as stopped. Once the simulation is stopped, no further
 * messages will be printed from any philosopher.
 *
 * @param philo Pointer to the philosopher performing the action.
 * @param action The action to print (e.g., THINKING, EATING, DIED).
 */
void	print_display_msg(t_philo *philo, t_action action)
{
	long	time;

	pthread_mutex_lock(&philo->sim->print_lock);

	if (is_simulation_stopped(philo->sim) && action != DIED)
	{
		pthread_mutex_unlock(&philo->sim->print_lock);
		return ;
	}
	time = get_sim_time(philo->sim);
	if (action == DIED)
	{
		printf("%ld %d died\n", time, philo->id);
		set_simulation_stopped(philo->sim, true);
	}
	else if (action == THINKING)
		printf("%ld %d is thinking\n", time, philo->id);
	else if (action == GOT_FORK1 || action == GOT_FORK2)
		printf("%ld %d has taken a fork\n", time, philo->id);
	else if (action == EATING)
		printf("%ld %d is eating\n", time, philo->id);
	else if (action == SLEEPING)
		printf("%ld %d is sleeping\n", time, philo->id);
	pthread_mutex_unlock(&philo->sim->print_lock);
}
