/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparisse <mparisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 20:14:10 by mparisse          #+#    #+#             */
/*   Updated: 2023/05/07 03:57:01 by mparisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>
# include <unistd.h>
// # include "libft/libft.h"
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
	pthread_mutex_t		mut_print;
	pthread_mutex_t		mut_dead;
	pthread_mutex_t		mut_finish;
	t_philo				*philo;
}	t_info;
// 
typedef struct s_philo
{
	int					index;
	int					count;
	long				eating_time;
	pthread_mutex_t		mut_eating_time;
	pthread_t			threads_philo;
	t_info				*infos;
	pthread_mutex_t		*left;
	pthread_mutex_t		*right;
	pthread_mutex_t		forks;
}		t_philo;

// tmp_utils
void		print_arguments(char **av);

// utils
long int	gettime(void);
void		ft_usleep(long ms);
int			is_dead(t_philo *philo);
void		prints(t_philo *philo, const char *state);

// parser
int			check_numbers(char **av);
int			parsing(char **av);

// init
int			init_struct_philo(t_info *info, char **av, char ac);
int			start_philo(t_info *info);

// main
void		*thread(void *data);

// mini lib
void		*ft_calloc(size_t nmemb, size_t size);
size_t		ft_strlen(char const *str);
void		ft_putchar_fd(char c, int fd);
int			ft_isdigit(int c);
int			ft_atoi(const char *str);
void		ft_putstr_fd(char const *s, int fd);

// mini lib 2
int			is_space(char c);

// routine
void		check_finish(t_info *info);

#endif