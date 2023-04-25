/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparisse <mparisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 20:14:10 by mparisse          #+#    #+#             */
/*   Updated: 2023/04/25 21:00:40 by mparisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include "libft/libft.h"
# include <sys/time.h>
# include <pthread.h>

typedef struct s_info
{
	int					nbs_of_philos;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
}	t_info;

typedef struct s_philo
{
	int					index;
	pthread_mutex_t		random_mutex;
	pthread_t			*threads_philo;
	pthread_mutex_t		*forks;
	t_info				*
}		t_philo;

void	print_arguments(char **av);

#endif