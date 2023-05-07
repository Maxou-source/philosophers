/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparisse <mparisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 20:13:48 by mparisse          #+#    #+#             */
/*   Updated: 2023/05/07 03:52:36 by mparisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	static t_info	info = {0};
	int				i;

	if ((ac >= 5 && ac <= 6) && parsing(av))
	{
		if (init_struct_philo(&info, av, ac) == 1)
			return (1);
		start_philo(&info);
	}
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
	free(info.philo);
}

// philo negativs number