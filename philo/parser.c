/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparisse <mparisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 05:04:37 by mparisse          #+#    #+#             */
/*   Updated: 2023/05/10 22:59:40 by mparisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_numbers(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (!ft_isdigit(av[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	parsing(char **av)
{
	int	i;
	int	value;

	if (!check_numbers(av))
		return (0);
	i = 1;
	if (ft_atoi(av[1]) == 0)
		return (0);
	while (av[i])
	{
		value = ft_atoi(av[i]);
		if (value == -1)
			return (0);
		i++;
	}
	return (1);
}
