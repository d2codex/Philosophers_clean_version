/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diade-so <diade-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 13:45:29 by diade-so          #+#    #+#             */
/*   Updated: 2025/08/19 14:59:19 by diade-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

// enums and structs

typedef enum	e_action
{
	GOT_FORK1,
	GOT_FORK2,
	EATING,
	SLEEPING,
	THINKING,
	DIED
}		t_action;

typedef struct	s_args
{
	int	num_philos;	// Number of philosphers 
	long	time_to_die;	// Time (ms) until a philo dies without eating
	long	time_to_eat;	// Time (ms) a philo spends eating
	long	time_to_sleep;	// Time (ms) a philo spends sleeping
	int	meal_goal;	// Number of meals each philo must eat (0 = no limit)
}		t_args;

typedef struct	s_philo
{
	int	id;			// Philo ID
	pthread_t	thread;		// Thread representing this philo
	long		last_meal_time; // Timestamp of last meal start time
	int		meals_eaten;	// Number of meals consumed
	pthread_mutex_t	meal_lock;	// Protects last_meal_time and meals_eaten
	pthread_mutex_t *fork1;		// Pointer to fork1 mutex
	pthread_mutex_t	*fork2;		// Pointer to fork2 mutex
}		t_philo;

typedef	struct	s_sim
{
	t_args		args;		// Simulation parameters
	t_philo		*philos;	// Array of philos
	pthread		*forks;		// Array of forks
	pthread		monitor_thread; // Thread monitoring philos for death or meal goal
	pthread_mutex_t	print_lock;	// Mutex to protect output
	pthread_mutex_t	stop_lock;	// Mutex to protect sim_stopped flag
	bool	sim_stopped;		// Flag indicating whether simulation should stop
}		t_sim;

#endif
