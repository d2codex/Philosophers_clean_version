/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diade-so <diade-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 15:22:21 by diade-so          #+#    #+#             */
/*   Updated: 2025/08/19 18:07:48 by diade-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_sim sim;

	// Initialize simulation arguments
	if (init_args(ac, av, &sim.args) != 0)
		return (1);
/*
	if (sim.args.num_philos == 1)
	{
		handle_one_philo(&sim);
		return 0;
	}	
*/
	// Initialize forks and philosophers
	if (init_forks(&sim) != 0)
		return (1);
	if (init_philos(&sim) != 0)
		return (1);

	// Initialize general mutexes
	init_mutexes(&sim);


	printf("\nForks addresses:\n");
	int i = 0;
	while (i < sim.args.num_philos)
	{
		printf("Fork %d: %p\n", i, (void *)&sim.forks[i]);
		i++;
	}

	// Print philosopher initial values
	printf("\nPhilosophers:\n");
	i = 0;
	while (i < sim.args.num_philos)
	{
		printf("Philo %d: id=%d, meals_eaten=%d, last_meal_time=%ld, fork1=%p, fork2=%p\n",
				i + 1,
				sim.philos[i].id,
				sim.philos[i].meals_eaten,
				sim.philos[i].last_meal_time,
				(void *)sim.philos[i].fork1,
				(void *)sim.philos[i].fork2);
		i++;
	}	

	return (0);
}

