/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwanetta <dwanetta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 03:17:50 by dwanetta          #+#    #+#             */
/*   Updated: 2021/01/16 20:25:02 by dwanetta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_print_char(va_list ap, t_flag *flag, int *return_value)
{
	char	c;

	flag->zero = 0;
	flag->dot = 0;
	flag->count_simbol = 0;
	c = (char)va_arg(ap, int);
	*return_value += ft_print_format(*flag, 1, 1);
	flag->size_width++;
	*return_value += ft_putchar(c);
	*return_value += ft_print_format_left(flag, 1, 1);
}

void	ft_print_str(va_list ap, t_flag *flag, int *return_value)
{
	char	*str;
	int		size;

	flag->zero = 0;
	str = va_arg(ap, char *);
	if (str == NULL)
		str = "(null)";
	size = ft_strlen(str);
	if (size > flag->count_simbol && flag->dot == 1 && flag->count_simbol >= 0)
		size = flag->count_simbol;
	flag->count_simbol = 0;
	*return_value += ft_print_format(*flag, size, 1);
	flag->size_width++;
	*return_value += ft_putstr(str, size);
	*return_value += ft_print_format_left(flag, size, 1);
}

void	ft_print_procent(t_flag *flag, int *return_value)
{
	flag->dot = 0;
	flag->count_simbol = 0;
	*return_value += ft_print_format(*flag, 1, 1);
	flag->size_width++;
	*return_value += ft_putchar('%');
	*return_value += ft_print_format_left(flag, 1, 1);
}
