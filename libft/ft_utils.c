/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparisse <mparisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 17:33:07 by mparisse          #+#    #+#             */
/*   Updated: 2023/04/14 20:57:28 by mparisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstr(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (write(2, "(null)", 6));
	while (str[i])
		i++;
	return (write(2, str, i));
}

int	ft_putchar(int c)
{
	return (write(2, &c, 1));
}

int	ft_putnbr(uintptr_t n, uintptr_t base, int upper)
{
	static int	count;

	count = 0;
	if (n >= base)
		ft_putnbr(n / base, base, upper);
	count += ft_putchar(BASE[n % base + base * upper]);
	return (count);
}

// int	ft_putnbr_extra2(uintptr_t n,uintptr_t base)
// {
// 	static int	count;

// 	count = 0;
// 	if (n >= base)
// 		ft_putnbr_extra2(n / base, base);
// 	count += ft_putchar(BASE_MAJ[n % base]);
// 	return (count);
// }
// int	ft_put_unsigned(unsigned int n)
// {
// 	return (ft_putnbr_modif(n));	 
// }
/*
int	ft_putnbr(int nb)
{
	unsigned int	n;

	n = -(nb < 0) * nb + (nb >= 0) * nb;
	if (nb < 0)
		write(1, "-", 1);
	if (n <= 9)
	{
		return (ft_putchar_modif(n + 48));
	}
	else
	{
		return (ft_putnbr(n / 10));
		return (ft_putnbr(n % 10));
	}
}*/
