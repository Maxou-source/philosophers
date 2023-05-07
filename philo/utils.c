/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparisse <mparisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 04:48:27 by mparisse          #+#    #+#             */
/*   Updated: 2023/05/06 23:56:43 by mparisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	gettime(void)
{
	struct timeval	time;
	long int		time_in_ms;

	if (gettimeofday(&time, NULL) == -1)
		return (-1);
	time_in_ms = ((time.tv_sec) * 1000 + (time.tv_usec) / 1000);
	return (time_in_ms);
}
/*
the function gettime gets the time of day and converts it
milliseconds

time.tv_sec is the time in seconds
we multiply it by 1000 to get the time in milliseconds

time.tv_usec is the additional time in microseconds after the 
time in seconds time.tv_sec
we divide the time by 1000 to get the time in milliseconds

we add the two times to each other to get the total time of milliseconds
since the epoch
*/

void	ft_usleep(long ms)
{
	long	begin;

	begin = gettime();
	while (gettime() - begin < ms)
		usleep(10);
}
/*
time to wait -> 90
example begin = 1000

this means we will call usleep at least 9 times

since the usleep function is sure to work everytime we divide it
small portion of 10 so we are sure that we at least wait a bit
*/

int	is_dead(t_philo *philo)
{
	int	dead;

	pthread_mutex_lock(&philo->infos->mut_dead);
	dead = philo->infos->dead;
	pthread_mutex_unlock(&philo->infos->mut_dead);
	return (dead);
}
/*
this function simply gets the returns the value
of is one philo dead or not
*/

void	prints(t_philo *philo, const char *state)
{
	pthread_mutex_lock(&philo->infos->mut_print);
	if (is_dead(philo))
	{
		pthread_mutex_unlock(&philo->infos->mut_print);
		return ;
	}
	printf("%08ld %d %s\n", gettime() - philo->infos->time_stamp,
		philo->index + 1, state);
	pthread_mutex_unlock(&philo->infos->mut_print);
}
/*
prints
*/