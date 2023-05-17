/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparisse <mparisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 03:51:54 by mparisse          #+#    #+#             */
/*   Updated: 2023/05/10 23:31:16 by mparisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	taken_fork(t_philo *philo)
{
	if (philo->index % 2 == 0)
	{
		pthread_mutex_lock(philo->left);
		prints(philo, "has taken a fork");
		if (philo->left == philo->right)
		{
			pthread_mutex_unlock(philo->left);
			return (1);
		}
		pthread_mutex_lock(philo->right);
		prints(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->right);
		prints(philo, "has taken a fork");
		pthread_mutex_lock(philo->left);
		prints(philo, "has taken a fork");
	}
	return (0);
}

int	next_step_of_routine(t_philo *philo)
{
	prints(philo, "is eating");
	pthread_mutex_lock(&philo->mut_eating_time);
	philo->eating_time = gettime();
	pthread_mutex_unlock(&philo->mut_eating_time);
	ft_usleep(philo->infos->time_to_eat);
	philo->count++;
	if (philo->count == philo->infos->nb_meal)
	{
		pthread_mutex_lock(&philo->infos->mut_finish);
		philo->infos->finish_philo++;
		pthread_mutex_unlock(&philo->infos->mut_finish);
		pthread_mutex_unlock(philo->left);
		pthread_mutex_unlock(philo->right);
		return (1);
	}
	pthread_mutex_unlock(philo->left);
	pthread_mutex_unlock(philo->right);
	prints(philo, "is sleeping");
	ft_usleep(philo->infos->time_to_sleep);
	prints(philo, "is thinking");
	return (0);
}

// 	description of the begg of the function thread:
// so first of all once we enter the function we wait for a bit smaller
// then philo->time_to_eat
// why? still need more explanation
// probably:
// waiting for half
// then we lock the count for the other part of the philos
// the left and right fork so now only half of the philos
// can eat.
// -we print the message philos are eating
// -getting at what time the philo is eating in milliseconds
// -usleep for the time of eating
// -increases the number of count which the count of meal
// -if the philo has done all his meal we exit the current thread and
// increase the number of philo
// who had finished they're meal
// -we continue the by unlocking the forks the philo was eating
// -in the case of impair number as the number of philo we need to
// wait a bit or else they will to many person on one fork
void	*thread(void *data)
{
	t_philo	*philo;

	philo = data;
	if (philo->index % 2 == 0)
		ft_usleep(philo->infos->time_to_eat * 0.25);
	while (!is_dead(philo))
	{
		if (philo->infos->nbs_of_philos % 2 && philo->count)
			ft_usleep(philo->infos->time_to_die * 0.2);
		if (taken_fork(philo))
			break ;
		if (next_step_of_routine(philo))
			return (0);
	}
	return (NULL);
}

int	death(t_info *info)
{
	int		i;
	long	eating_time;

	i = -1;
	while (++i < info->nbs_of_philos)
	{
		pthread_mutex_lock(&info->philo[i].mut_eating_time);
		eating_time = gettime() - info->philo[i].eating_time;
		pthread_mutex_unlock(&info->philo[i].mut_eating_time);
		if (eating_time >= info->time_to_die)
		{
			pthread_mutex_lock(&info->mut_dead);
			info->dead = 1;
			pthread_mutex_unlock(&info->mut_dead);
			pthread_mutex_lock(&info->mut_print);
			printf("%08ld %d died\n", gettime() - info->time_stamp, i + 1);
			pthread_mutex_unlock(&info->mut_print);
			return (1);
		}
	}
	return (0);
}

/*
in this function we are checking if the philos are either done eating
all they're meal or one philo has died

-so we are first assigning the eating time to the actual time minus the
last time a philo has eaten
-we are then checking if the eating time is greater then the time to die
if it is the case then we change the value to dead
*/
void	check_finish(t_info *info)
{
	while (1)
	{
		if (death(info))
			return ;
		pthread_mutex_lock(&info->mut_finish);
		if (info->finish_philo == info->nbs_of_philos)
		{
			pthread_mutex_unlock(&info->mut_finish);
			return ;
		}
		pthread_mutex_unlock(&info->mut_finish);
		usleep(100);
	}
}
