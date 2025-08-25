/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diade-so <diade-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 18:30:40 by diade-so          #+#    #+#             */
/*   Updated: 2025/08/20 20:04:38 by diade-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_sim(t_sim *sim, const char *msg)
{
	int	i;

	if (!sim)
		return ;
	if (msg)
		printf("%s\n", msg);
	if (sim->philos)
	{
		i = 0;
		while (i < sim->args.num_philos)
			pthread_mutex_destroy(&sim->philos[i++].meal_lock);
		free(sim->philos);
		sim->philos = NULL;
	}
	if (sim->forks)
	{
		i = 0;
		while (i < sim->args.num_philos)
			pthread_mutex_destroy(&sim->forks[i++]);
		free(sim->forks);
		sim->forks = NULL;
	}
	pthread_mutex_destroy(&sim->print_lock);
	pthread_mutex_destroy(&sim->stop_lock);
}
