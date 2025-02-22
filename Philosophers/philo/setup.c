/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smontuor <smontuor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 11:36:53 by smontuor          #+#    #+#             */
/*   Updated: 2024/07/18 14:01:32 by smontuor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_setup_mutexes(t_monitor *monitor, t_philo *philo,
		pthread_mutex_t *forks, int n)
{
	int	i;

	monitor->perished = 0;
	monitor->philo = philo;
	pthread_mutex_init(&monitor->snack_lock, NULL);
	pthread_mutex_init(&monitor->print_lock, NULL);
	pthread_mutex_init(&monitor->perish_lock, NULL);
	i = 0;
	while (i < n)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}

static void	ft_set_input(t_philo *philo, char **av)
{
	philo->tot_philo = ft_atoi(av[1]);
	philo->perish_time = ft_atoi(av[2]);
	philo->snack_time = ft_atoi(av[3]);
	philo->nap_time = ft_atoi(av[4]);
	if (av[5])
		philo->max_snacks = ft_atoi(av[5]);
	else
		philo->max_snacks = -1;
}

static void	ft_set_forks(t_philo *philo, pthread_mutex_t *forks, int i)
{
	if (i == 0)
	{
		philo[i].right_fork = &forks[philo[i].tot_philo - 1];
		philo[i].left_fork = &forks[i];
	}
	else if (i == philo[0].tot_philo - 1)
	{
		philo[i].right_fork = &forks[i];
		philo[i].left_fork = &forks[i - 1];
	}
	else
	{
		philo[i].left_fork = &forks[i];
		philo[i].right_fork = &forks[i - 1];
	}
}

static int	check_data(t_philo *philo, int tot_philo)
{
	if (tot_philo > MAX_PHILO)
	{
		write(2, "Error: too many philosophers\n", 30);
		return (1);
	}
	if (philo[0].perish_time < MIN_TIME)
	{
		write(2, "Error: perish time too short\n", 30);
		return (1);
	}
	if (philo[0].snack_time < MIN_TIME)
	{
		write(2, "Error: snack time too short\n", 29);
		return (1);
	}
	if (philo[0].nap_time < MIN_TIME)
	{
		write(2, "Error: nap time too short\n", 27);
		return (1);
	}
	return (0);
}

int	ft_setup_philo(t_philo *philo, t_monitor *monitor,
		pthread_mutex_t *forks, char **av)
{
	int	i;
	int	tot_philo;

	i = 0;
	tot_philo = ft_atoi(av[1]);
	while (i < tot_philo)
	{
		philo[i].id = i + 1;
		philo[i].snacking = 0;
		philo[i].snacks_eaten = 0;
		philo[i].snack_lock = &monitor->snack_lock;
		philo[i].print_lock = &monitor->print_lock;
		philo[i].perish_lock = &monitor->perish_lock;
		philo[i].perished = &monitor->perished;
		philo[i].last_snack = ft_get_time();
		philo[i].birth_time = ft_get_time();
		ft_set_input(&philo[i], av);
		ft_set_forks(philo, forks, i);
		i++;
	}
	return (check_data(philo, tot_philo));
}
