/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_lib_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparisse <mparisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 03:36:49 by mparisse          #+#    #+#             */
/*   Updated: 2023/05/07 03:54:34 by mparisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	long	res;
	int		negatif;

	res = 0;
	negatif = 1;
	while (is_space(*str) == 1)
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			negatif = negatif * -1;
		str++;
	}
	if (*str == '+' || *str == '-')
		return (ft_putstr_fd("Error!!\n", 1), exit(0), 0);
	while (ft_isdigit(*str))
	{
		res = res * 10 + (*str++ - 48);
		if (res * negatif > 2147483647 || res * negatif < -2147483648)
		{
			return (ft_putstr_fd("Error!!\n", 1), exit(0), 0);
		}
	}
	return (res * negatif);
}

void	ft_putstr_fd(char const *s, int fd)
{
	int	i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
		i++;
	write(fd, s, i);
}
