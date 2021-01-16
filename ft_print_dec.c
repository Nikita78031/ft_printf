/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_dec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwanetta <dwanetta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 03:18:35 by dwanetta          #+#    #+#             */
/*   Updated: 2021/01/16 20:25:37 by dwanetta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_print_dec(va_list ap, t_flag *flag, int *return_value)
{
	int	dec;
	int	size;

	dec = va_arg(ap, int);
	size = ft_chek(dec);
	if (flag->dot == 1 && flag->zero == 1 && flag->count_simbol >= 0)
		flag->zero = 0;
	*return_value += ft_print_format(*flag, size, dec);
	if (flag->size_width < 0)
	{
		flag->minus = 1;
		flag->size_width *= -1;
	}
	if (dec != 0 || flag->dot == 0 || flag->count_simbol != 0)
		*return_value += ft_putnbr(dec, 1);
	else
		flag->size_width++;
	if (dec >= 0)
		flag->size_width++;
	*return_value += ft_print_format_left(flag, size, dec);
}

void	ft_print_u_dec(va_list ap, t_flag *flag, int *return_value)
{
	unsigned int	u_dec;
	int				size;

	if (flag->dot == 1 && flag->count_simbol >= 0)
		flag->zero = 0;
	u_dec = va_arg(ap, unsigned int);
	size = ft_chek_u(u_dec);
	if (flag->size_width < 0)
	{
		flag->minus = 1;
		flag->size_width *= -1;
	}
	*return_value += ft_print_format(*flag, size, u_dec);
	if (u_dec != 0 || flag->dot == 0 || flag->count_simbol != 0)
		*return_value += ft_putnbr_u(u_dec);
	else
		flag->size_width++;
	flag->size_width++;
	*return_value += ft_print_format_left(flag, size, 1);
}
