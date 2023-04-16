/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparisse <mparisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 20:13:48 by mparisse          #+#    #+#             */
/*   Updated: 2023/04/16 19:13:06 by mparisse         ###   ########.fr       */
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
			if (ft_strlen(av[i]) == 1 && (av[i][j] == '-' || av[i][j] == '+'))
				return (0);
			if (ft_isdigit(av[i][j]) == 0 && av[i][j] != '+' && av[i][j] != '-')
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
	int value;

	if (!check_numbers(av))
		return (0);
	i = 1;
	if (ft_atoi(av[1]) == 0)
		return (0);
	while (av[i])
	{
		value = ft_atoi(av[i]);
		printf("value > %d\n", value);
		i++;
	}
	return (1);
}

int	main(int ac, char **av)
{
	if (ac != 5 || !parsing(av))
	{
		ft_putstr_fd("Error!!\n", 2);
		return (EXIT_FAILURE);
	}
	
}
