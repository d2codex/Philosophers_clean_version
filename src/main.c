/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diade-so <diade-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 15:22:21 by diade-so          #+#    #+#             */
/*   Updated: 2025/08/19 16:55:30 by diade-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_args args;

	if (init_args(ac, av, &args) != 0)
		return (1);

	printf("Number of philosophers: %d\n", args.num_philos);
	printf("Time to die (ms): %ld\n", args.time_to_die);
	printf("Time to eat (ms): %ld\n", args.time_to_eat);
	printf("Time to sleep (ms): %ld\n", args.time_to_sleep);
	printf("Meal goal: %d\n", args.meal_goal);

	return 0;
}
