/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smontuor <smontuor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 12:02:27 by smontuor          #+#    #+#             */
/*   Updated: 2024/07/12 12:26:15 by smontuor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check_num(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+')
		i++;
	if (str[i] == '0')
		return (1);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int	ft_check_args(int ac, char **av)
{
	if (ft_check_num(av[1]))
		return (write(2, "Invalid number of philosophers\n", 31));
	if (ft_check_num(av[2]))
		return (write(2, "Invalid time to die\n", 20));
	if (ft_check_num(av[3]))
		return (write(2, "Invalid time to eat\n", 20));
	if (ft_check_num(av[4]))
		return (write(2, "Invalid time to sleep\n", 22));
	if (ac == 6)
	{
		if (ft_check_num(av[5]))
			return (write(2, "Invalid number of times philosophers must eat\n"
					, 46));
	}
	return (0);
}
