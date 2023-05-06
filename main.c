/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparisse <mparisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 20:13:48 by mparisse          #+#    #+#             */
/*   Updated: 2023/05/06 05:03:13 by mparisse         ###   ########.fr       */
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
	int	value;

	if (!check_numbers(av))
		return (0);
	i = 1;
	if (ft_atoi(av[1]) == 0)
		return (0);
	while (av[i])
	{
		value = ft_atoi(av[i]);
		i++;
	}
	return (1);
}

void	prints(t_philo *philo, const char *state)
{
	pthread_mutex_lock(&philo->infos->mut_print);
	if (is_dead(philo))
	{
		pthread_mutex_unlock(&philo->infos->mut_print);
		return;
	}
	printf("%08ld %d %s\n", gettime() - philo->infos->time_stamp, philo->index, state);
	pthread_mutex_unlock(&philo->infos->mut_print);
}

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
		if (philo->index % 2 == 0)
		{
			pthread_mutex_lock(philo->left);
			prints(philo, "has taken a fork");
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
			return NULL;
		}
		pthread_mutex_unlock(philo->left);
		pthread_mutex_unlock(philo->right);
		prints(philo, "is sleeping");
		ft_usleep(philo->infos->time_to_sleep);
		prints(philo, "is thinking");	
	}
	return (NULL);
}

int	init_philo(int ac, char **av, t_info *info)
{
	int		i;

	(void) ac;
	info->nbs_of_philos = ft_atoi(av[1]);
	info->time_to_die = ft_atoi(av[2]);
	info->time_to_eat = ft_atoi(av[3]);
	info->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		info->nb_meal = ft_atoi(av[5]);
	info->philo = calloc(sizeof(t_philo), info->nbs_of_philos);
	if (!info->philo)
		exit(EXIT_FAILURE); // pas le droit oupsiii 
	pthread_mutex_init(&info->mut_print, NULL);
	pthread_mutex_init(&info->mut_dead, NULL);
	pthread_mutex_init(&info->mut_finish, NULL);
	info->time_stamp = gettime();
	i = 0;
	while (i < info->nbs_of_philos)
	{
		info->philo[i].index = i;
		info->philo[i].infos = info;
		info->philo[i].eating_time = info->time_stamp;
		pthread_mutex_init(&info->philo[i].forks, NULL);
		pthread_mutex_init(&info->philo[i].mut_eating_time, NULL);
		info->philo[i].left = &info->philo[i].forks;
		if (i != info->nbs_of_philos - 1)
			info->philo[i].right = &info->philo[i + 1].forks;
		else
			info->philo[i].right = &info->philo[0].forks;
		i++;
	}
	i = 0;
	while (i < info->nbs_of_philos)
	{
		pthread_create(&info->philo[i].threads_philo, NULL, &thread, (void *)&info->philo[i]);
		i++;
	}
	return (1);
}

void check_finish(t_info *info)
{
	long eating_time;
	int	i;

	while (1)
	{
		i = 0;
		while (i < info->nbs_of_philos)
		{
			pthread_mutex_lock(&info->philo[i].		mut_eating_time);
			eating_time = gettime() - info->philo[i].eating_time;
			pthread_mutex_unlock(&info->philo[i].mut_eating_time);
			if (eating_time >= info->time_to_die)
			{
				pthread_mutex_lock(&info->mut_dead);
				info->dead = 1;
				pthread_mutex_unlock(&info->mut_dead);
				pthread_mutex_lock(&info->mut_print);
				printf("%08ld %d has died\n", gettime() - info->time_stamp, i);
				pthread_mutex_unlock(&info->mut_print);
				return ;
			}
			i++;
		}
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

int	main(int ac, char **av)
{
	t_info	info;
	int	i;
	
	memset(&info, 0, sizeof(t_info));
	if ((ac >= 5 && ac <= 6) && parsing(av))
		init_philo(ac, av, &info);
	else
	{
		ft_putstr_fd("Error\n", 2);
		return (EXIT_FAILURE);
	}
	check_finish(&info);
	i = 0;
	while (i < info.nbs_of_philos)
	{
		pthread_join(info.philo[i].threads_philo, 0);
		i++;
	}
}
