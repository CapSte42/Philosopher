/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smontuor <smontuor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 11:54:56 by smontuor          #+#    #+#             */
/*   Updated: 2024/07/18 13:58:28 by smontuor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

/* define the max number of philosophers */
# define MAX_PHILO 200
/* define the min time for a philosopher to perish, snack, or nap */
# define MIN_TIME 60
/*struct for the philosopher*/
typedef struct s_philo
{
	int				id;				// id [int] of the philosopher
	pthread_t		thread;			// thread [pthread_t] of the philosopher
	int				snacking;		// 0 or 1 if the philosopher is eating
	int				snacks_eaten;	// number of snacks eaten
	size_t			last_snack;		// time of the last snack
	size_t			perish_time;	// min 60
	size_t			snack_time;		// min 60
	size_t			nap_time;		// min 60
	size_t			birth_time;		// time of birth
	int				tot_philo;		// max 200
	int				max_snacks;		// av[5] or -1
	int				*perished;		// pointer to monitor->perished
	pthread_mutex_t	*left_fork;		// pointer to the left fork
	pthread_mutex_t	*right_fork;	// pointer to the right fork
	pthread_mutex_t	*print_lock;	// pointer to monitor->print_lock
	pthread_mutex_t	*snack_lock;	// pointer to monitor->snack_lock
	pthread_mutex_t	*perish_lock;	// pointer to monitor->perish_lock
}	t_philo;

/*struct for the monitor*/
typedef struct s_monitor
{
	int				perished;		// number of philosophers who have died
	pthread_mutex_t	perish_lock;	// lock for perished
	pthread_mutex_t	print_lock;		// lock for printing
	pthread_mutex_t	snack_lock;		// lock for snacking
	t_philo			*philo;			// pointer to the philosophers
}	t_monitor;

// philo_life.c
void	ft_snack(t_philo *philo);
void	ft_nap(t_philo *philo);
void	*ft_think_about_life(void *p);

// philosopher.c
int		ft_create_philos(t_monitor *monitor);
int		ft_is_alive(t_philo *philo);

// setup.c
void	ft_setup_mutexes(t_monitor *monitor, t_philo *philo,
			pthread_mutex_t *forks, int n);
int		ft_setup_philo(t_philo *philo, t_monitor *monitor,
			pthread_mutex_t *forks, char **av);

// supervisor.c
void	*ft_supervisor(void *p);

// parsing.c
int		ft_check_args(int ac, char **av);
int		ft_check_num(char *str);

// utils.c
void	ft_print(t_philo *philo, int id, char *msg);
int		ft_my_usleep(size_t time);
size_t	ft_get_time(void);
int		ft_atoi(const char *str);
void	ft_free_all(t_monitor *monitor, pthread_mutex_t *forks, t_philo *philo);

#endif