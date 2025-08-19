/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diade-so <diade-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 13:45:29 by diade-so          #+#    #+#             */
/*   Updated: 2025/08/19 22:55:05 by diade-so         ###   ########.fr       */
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
# include <limits.h>

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
	int	meal_goal;	// Number of meals each philo must eat (-1 = no limit)
}		t_args;

typedef struct s_sim t_sim;

typedef struct	s_philo
{
	int	id;			// Philo ID
	pthread_t	thread;		// Thread representing this philo
	long		last_meal_time; // Timestamp of last meal start time
	int		meals_eaten;	// Number of meals consumed
	pthread_mutex_t	meal_lock;	// Protects last_meal_time and meals_eaten
	pthread_mutex_t *fork1;		// Pointer to fork1 mutex
	pthread_mutex_t	*fork2;		// Pointer to fork2 mutex
	t_sim           *sim;
}		t_philo;

typedef	struct	s_sim
{
	t_args		args;		// Simulation parameters
	t_philo		*philos;	// Array of philos
	pthread_t	monitor_thread; // Thread monitoring philos for death or meal goal
	pthread_mutex_t	*forks;		// Array of forks
	pthread_mutex_t	print_lock;	// Mutex to protect output
	pthread_mutex_t	stop_lock;	// Mutex to protect sim_stopped flag
	t_sim           *sim;
	bool	sim_stopped;		// Flag indicating whether simulation should stop
}		t_sim;

// Prototypes

// utils.c
int     ft_strlen(const char *str);
int     ft_atol(const char *str, long *out);
int     ft_atoi(const char *str, int *out);

// init.c
int     init_args(int ac, char **av, t_args *args);
int     init_forks(t_sim *sim);
int     init_philos(t_sim *sim);
void    init_mutexes(t_sim *sim);

// errors.c
int     error_return(const char *msg);

// time.c
long    get_time_ms(void);
long    get_sim_time(t_sim *sim);
void    smart_sleep(t_sim *sim, long ms);
void    wait_for_start(t_sim *sim);

// cleanup.c
void    cleanup(t_sim *sim, const char *msg);
void destroy_mutexes(t_sim *sim);

// routine.c
void    *philo_routine(void *arg);
void    handle_one_philo(t_sim *sim);

// actions.c
void    grab_forks(t_philo *philo);
void    eat(t_philo *philo);
void    slumber(t_philo *philo);
void    think(t_philo *philo);

// print.c
void    print_usage(void);
void    print_display_msg(t_philo *philo, t_action action);

// monitor.c
t_philo *check_starvation(t_sim *sim);
int     check_meal_goal(t_sim *sim);
void    *monitor(void *arg);
bool    is_simulation_stopped(t_sim *sim);
void    set_simulation_stopped(t_sim *sim, bool value);

#endif
