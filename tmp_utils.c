/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparisse <mparisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 22:47:41 by mparisse          #+#    #+#             */
/*   Updated: 2023/04/16 22:58:53 by mparisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_arguments(char **av)
{
	int i;
	// number_of_philosophers    time_to_die   time_to_eat    time_to_sleep
	// [number_of_times_each_philosopher_must_eat]
	i = 1;
	while (av[i])
	{
		if (i == 1)
			printf("numbers of philosophers : %d\n", ft_atoi(av[i]));
		if (i == 2)
			printf("time to die             : %d\n", ft_atoi(av[i]));
		if (i == 3)
			printf("time to eat             : %d\n", ft_atoi(av[i]));
		if (i == 4)
			printf("time to sleep           : %d\n", ft_atoi(av[i]));
		i++;
	}
}