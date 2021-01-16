/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_format.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwanetta <dwanetta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 03:19:49 by dwanetta          #+#    #+#             */
/*   Updated: 2021/01/16 20:26:52 by dwanetta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_flag_init(t_flag *flag)
{
	flag->dot = 0;
	flag->zero = 0;
	flag->minus = 0;
	flag->size_width = 0;
	flag->count_simbol = 0;
}

int		ft_print_format(t_flag flag, int size, long int value)
{
	int		return_value;
	char	symbol;

	return_value = 0;
	if (value == 0 && flag.dot != 0 && flag.count_simbol == 0)
		flag.size_width += 1;
	if (flag.zero == 0 || flag.count_simbol > 0)
		symbol = ' ';
	else
		symbol = '0';
	if (value < 0 && symbol != ' ')
		return_value += ft_putchar('-');
	if (value < 0)
		flag.size_width -= 1;
	if (flag.count_simbol < size)
		flag.count_simbol = size;
	while (((flag.size_width--) - flag.count_simbol > 0) && flag.minus == 0)
		return_value += ft_putchar(symbol);
	if (value < 0 && symbol == ' ')
		return_value += ft_putchar('-');
	while (((flag.count_simbol--) - size) > 0)
		return_value += ft_putchar('0');
	return (return_value);
}

int		ft_print_format_left(t_flag *flag, int size, long int value)
{
	int	return_value;

	return_value = 0;
	if (flag->size_width <= 0)
	{
		flag->minus = 1;
		flag->size_width *= -1;
		if (value >= 0)
			flag->size_width += 2;
	}
	if (flag->minus == 1 && flag->count_simbol < size)
		flag->count_simbol = size;
	while (flag->minus == 1 &&
			(flag->size_width--) - flag->count_simbol - 1 > 0)
		return_value += ft_putchar(' ');
	return (return_value);
}
