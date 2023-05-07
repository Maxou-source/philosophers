/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparisse <mparisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 05:46:01 by mparisse          #+#    #+#             */
/*   Updated: 2023/05/07 03:49:13 by mparisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_struct_philo(t_info *info, char **av, char ac)
{
	int *const	ptr = &info -> nbs_of_philos;
	int			i;

	i = -1;
	while (++i < 4 + (ac > 5))
	{
		*(ptr + i) = ft_atoi(av[1 + i]);
		if (*(ptr + i) < 0)
		{
			ft_putstr_fd("Error (negatives values)\n", 2);
			return (1);
		}
	}
	info->philo = ft_calloc(sizeof(t_philo), info->nbs_of_philos);
	if (!info->philo)
		return (EXIT_FAILURE);
	if (pthread_mutex_init(&info->mut_print, NULL))
		return (EXIT_FAILURE);
	if (pthread_mutex_init(&info->mut_dead, NULL))
		return (EXIT_FAILURE);
	if (pthread_mutex_init(&info->mut_finish, NULL))
		return (EXIT_FAILURE);
	info->time_stamp = gettime();
	return (0);
}

// this functions will initialize
// all  the data necessary for the start of the
// program
// -it will initialize all the mutexs needed for the protection
// of different variables
// mut_print -> protects the printf function the printfs wont be mixt up
// mut_dead -> protects the threads from reading and writing on the variable
// of death
// mut_finish -> will protect the variable responsible for the count 
// of the minimum meal

int	start_philo(t_info *info)
{
	int		i;
	t_philo	*philo;

	philo = info->philo;
	i = -1;
	while (++i < info->nbs_of_philos)
	{
		philo[i].index = i;
		philo[i].infos = info;
		philo[i].eating_time = info->time_stamp;
		pthread_mutex_init(&philo[i].forks, NULL);
		pthread_mutex_init(&philo[i].mut_eating_time, NULL);
		philo[i].left = &philo[i].forks;
		if (i != info->nbs_of_philos - 1)
			philo[i].right = &philo[i + 1].forks;
		else
			philo[i].right = &philo[0].forks;
	}
	i = -1;
	while (++i < info->nbs_of_philos)
		pthread_create(&info->philo[i].threads_philo, NULL,
			&thread, (void *)&info->philo[i]);
	return (1);
}
/*
this function will init all the philos individually  and start the 
routine in the previous init function
I initiliazed a tabs of struct.
each philo has its own structure containing a thread and its fork associated

forks:
the fork one the left is the fork that belongs to the philo at the 
start of the program. (lets say the original one)
but the actual philo needs a fork on the right
so we set the fork to the right as the next philos left fork
and the last philo right fork is the first philo left fork
*/