/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparisse <mparisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 20:14:10 by mparisse          #+#    #+#             */
/*   Updated: 2023/05/06 04:49:42 by mparisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include "libft/libft.h"
# include <sys/time.h>
# include <pthread.h>

typedef struct s_philo	t_philo;

typedef struct s_info
{
	int					nbs_of_philos;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					nb_meal;
	int					minimum_meal[2];
	long int			current;
	int					dead;
	int					finish_philo;
	long int			time_stamp;
	pthread_mutex_t		mut_print; //mutex printf
	pthread_mutex_t		mut_dead; //mutex dead
	pthread_mutex_t		mut_finish; // mutex repas termine
	t_philo				*philo;
}	t_info;
// 
typedef struct s_philo
{
	int					index;
	int					count;
	long				eating_time; //temp correspondant au dernier repas du philo
	pthread_mutex_t		mut_eating_time; // protect eating time philo
	pthread_t			threads_philo;
	t_info				*infos;
	pthread_mutex_t		*left;
	pthread_mutex_t		*right;
	pthread_mutex_t		forks; // mutex forks
}		t_philo;

void		print_arguments(char **av);
long int	gettime(void);
void		ft_usleep(long ms);
int			is_dead(t_philo *philo);

#endif