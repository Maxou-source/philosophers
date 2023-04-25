/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparisse <mparisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 20:13:48 by mparisse          #+#    #+#             */
/*   Updated: 2023/04/25 21:05:24 by mparisse         ###   ########.fr       */
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

pthread_mutex_t	lock;
int				counter;

void	*thread(void *data)
{
	t_philo	*philo;

	philo = (void *)data;
	pthread_mutex_lock(&philo->random_mutex);
	printf("philo %d created\n", philo->index);
	pthread_mutex_unlock(&philo->random_mutex);
	return (philo);
}

int	init_forks_mutex(t_philo *philo)
{
	int	i;

	i = 0;
	philo->forks = malloc(sizeof(pthread_mutex_t) * philo->nbs_of_philos);
	while (i < philo->nbs_of_philos)
	{
		pthread_mutex_init(&philo->forks[i], NULL);
		pthread_mutex_init(&philo->random_mutex, NULL);
		i++;
	}
	return (1);
}

int	init_philo(char **av, t_philo *philo, t_info *info)
{
	int	i;

	i = 1;
	info->nbs_of_philos = ft_atoi(av[1]);
	info->time_to_die = ft_atoi(av[2]);
	info->time_to_eat = ft_atoi(av[3]);
	info->time_to_sleep = ft_atoi(av[4]);
		i++;
	philo->threads_philo = malloc(sizeof(pthread_t) * info->nbs_of_philos);
	if (!philo->threads_philo)
		exit(0);
	i = 0;
	init_forks_mutex(philo);
	// pthread_mutex_init(&lock, NULL);
	while (i < info->nbs_of_philos)
	{
		// philo[i]-index = i;
		i++;
	}
	i = 0;
	while (i < info->nbs_of_philos)
	{
		pthread_create(&philo->threads_philo[i], NULL, &thread, (void *)philo);
		i++;
	}
	i = 0;
	while (i < info->nbs_of_philos)
	{
		pthread_join(philo->threads_philo[i], 0);
		i++;
	}
	pthread_mutex_destroy(&lock);
	free(philo->threads_philo);
	i = 0;
	return (1);
}

int	main(int ac, char **av)
{
	t_philo	philo;
	t_info	info;

	// void *ret;
	// struct timeval current_time;
	// pthread_t thread_test = 0;
	if (ac != 5 || !parsing(av))
	{
		ft_putstr_fd("Error\n", 2);
		return (EXIT_FAILURE);
	}
	print_arguments(av);
	init_philo(av, &philo);
	// thread(&philo);
	// gettimeofday(&current_time, NULL);
	// printf("seconds : %ld micro second : %ld\n", current_time.tv_sec,
	// current_time.tv_usec);
	// if (pthread_create(&thread_test, NULL, thread, "thread 1") != 0)
	// 	printf("ya haja\n");
	// pthread_join(thread_test, &ret);
	// printf("hello wolrd!\n");
}

// ./philo -1 23 556 1
// ./philo 11 23 556 4-
// ./philo 5 600 200 200 100
