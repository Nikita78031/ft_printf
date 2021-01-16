/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwanetta <dwanetta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 17:01:37 by dwanetta          #+#    #+#             */
/*   Updated: 2021/01/16 20:23:44 by dwanetta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_chek_nbr(int tmp)
{
	int	i;

	i = 1;
	while (1)
	{
		tmp /= 10;
		if (tmp == 0)
			break ;
		i *= 10;
	}
	return (i);
}

int	ft_chek_nbr_u(unsigned int tmp)
{
	int	i;

	i = 1;
	while (1)
	{
		tmp /= 10;
		if (tmp == 0)
			break ;
		i *= 10;
	}
	return (i);
}

int	ft_putnbr(int n, int flag)
{
	int	i;
	int	minus;
	int	return_value;

	minus = 1;
	return_value = 0;
	if (n < 0)
	{
		if (flag == -1)
			return_value += ft_putchar('-');
		minus = -1;
	}
	i = ft_chek_nbr(n);
	if (n == 0)
		return_value += ft_putchar('0');
	else
		while (i != 0)
		{
			return_value += ft_putchar((char)(48 + ((n / i) * minus)));
			n %= i;
			i /= 10;
		}
	return (return_value);
}

int	ft_putnbr_u(unsigned int n)
{
	int	i;
	int	return_value;

	return_value = 0;
	i = ft_chek_nbr_u(n);
	if (n == 0)
		return_value += ft_putchar('0');
	else
		while (i != 0)
		{
			return_value += ft_putchar((char)(48 + (n / i)));
			n %= i;
			i /= 10;
		}
	return (return_value);
}
