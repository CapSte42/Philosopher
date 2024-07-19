/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smontuor <smontuor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:11:16 by smontuor          #+#    #+#             */
/*   Updated: 2024/07/12 12:26:15 by smontuor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_create_philos(t_monitor *monitor)
{
	int			i;
	int			tot_philo;
	pthread_t	supervisor;

	i = 0;
	tot_philo = monitor->philo[0].tot_philo;
	while (i < tot_philo)
	{
		if (i % 2 == 0)
			ft_my_usleep(1);
		if (pthread_create(&monitor->philo[i].thread, NULL,
				&ft_think_about_life, &monitor->philo[i]) != 0)
			return (write(2, "Error: failed to create a thread\n", 33), -1);
		i++;
	}
	if (pthread_create(&supervisor, NULL, &ft_supervisor, monitor->philo) != 0)
		return (write(2, "Error: failed to create a thread\n", 33), -1);
	if (pthread_join(supervisor, NULL) != 0)
		return (write(2, "Error: failed to join the threads\n", 34), -1);
	i = -1;
	while (++i < tot_philo)
		if (pthread_join(monitor->philo[i].thread, NULL) != 0)
			return (write(2, "Error: failed to join the threads\n", 34), -1);
	return (0);
}
