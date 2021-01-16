/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwanetta <dwanetta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 16:29:58 by dwanetta          #+#    #+#             */
/*   Updated: 2021/01/16 20:27:01 by dwanetta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_print_hex(va_list ap, char fmt, t_flag *flag, int *return_value)
{
	int				size;
	char			*hex;
	unsigned int	u_dec;

	u_dec = va_arg(ap, unsigned int);
	ft_puthex(fmt, u_dec, &hex);
	size = ft_strlen(hex);
	if (flag->dot == 1 && flag->count_simbol >= 0)
		flag->zero = 0;
	if (flag->dot == 1 && flag->count_simbol == 0 && u_dec == 0)
		size = 0;
	if (flag->size_width < 0)
	{
		flag->minus = 1;
		flag->size_width *= -1;
	}
	*return_value += ft_print_format(*flag, size, 1);
	flag->size_width++;
	*return_value += ft_putstr(hex, size);
	*return_value += ft_print_format_left(flag, size, 1);
	if (hex != NULL)
		free(hex);
}

void	ft_print_pointer(va_list ap, t_flag *flag, int *return_value)
{
	int						size;
	char					*hex;
	unsigned long long int	ull_dec;

	ull_dec = va_arg(ap, unsigned long long int);
	ft_puthex_pointer(ull_dec, &hex);
	if (flag->size_width > 0)
		flag->size_width -= 2;
	else if (flag->size_width < 0)
		flag->size_width += 2;
	size = ft_strlen(hex);
	if (flag->dot == 1 && flag->count_simbol == 0 && ull_dec == 0)
		size = 0;
	*return_value += ft_print_format(*flag, size, 1);
	*return_value += ft_putchar('0');
	*return_value += ft_putchar('x');
	flag->size_width++;
	*return_value += ft_putstr(hex, size);
	if (flag->size_width == 0)
		flag->size_width = 1;
	*return_value += ft_print_format_left(flag, size, 1);
	if (hex != NULL)
		free(hex);
}
