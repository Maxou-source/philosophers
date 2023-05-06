/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparisse <mparisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 15:04:07 by mparisse          #+#    #+#             */
/*   Updated: 2023/04/26 01:54:00 by mparisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <limits.h>

static int	is_space(char c)
{
	if ((c >= '\t' && c <= '\r') || c == ' ')
		return (1);
	return (0);
}

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
			printf(">>> %ld\n", res);
			return (ft_putstr_fd("Error!!\n", 1), exit(0), 0);
		}
	}
	return (res * negatif);
}
