/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwanetta <dwanetta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 16:20:36 by dwanetta          #+#    #+#             */
/*   Updated: 2021/01/06 16:24:40 by dwanetta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int ft_check_specifier(const char *fmt)
{
	int i;
	int j;
	char *flags;

	j = 1;
	flags = "cspdiuxX%";
	while (fmt[j] != '\0')
	{
		i = 0;
		while (flags[i] != '\0')
		{
			if (flags[i] == fmt[j])
				return (j + 1);
			i++;
		}
		j++;
	}
	return (0);
}

void chek_size_flags(va_list ap, const char *fmt, int *size, int *i)
{
	while (fmt[*i] != '\0')
	{
		if (fmt[*i] == '.')
		{
			*i -= 1;
			break;
		}
		if (fmt[*i + 1] == '-')
			break;
		if (fmt[*i] == '*')
		{
			*size = va_arg(ap, int);
			break;
		}
		else if (fmt[*i] != '0')
		{
			*size = ft_atoi(fmt + *i);
			break;
		}
		*i += 1;
	}
}

int ft_print_format(t_flag flag, int size, long int value)
{
	int return_value;
	char symbol;

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

int ft_print_format_left(t_flag *flag, int size, long int value)
{
	int return_value;

	return_value = 0;
	if (flag->size_width < 0)
	{
		flag->minus = 1;
		flag->size_width *= -1;
		if (value >= 0)
			flag->size_width += 2;
	}
	if (flag->minus == 1 && flag->count_simbol < size)
		flag->count_simbol = size;
	while (flag->minus == 1 && (flag->size_width--) - flag->count_simbol - 1 > 0)
		return_value += ft_putchar(' ');
	return (return_value);
}

void ft_print_dec(va_list ap, t_flag *flag, int *return_value)
{
	int dec;
	int size;

	dec = va_arg(ap, int);
	size = ft_chek(dec);
	*return_value += ft_print_format(*flag, size, dec);
	if (dec != 0 || flag->dot == 0 || flag->count_simbol != 0)
	    *return_value += ft_putnbr(dec, 1);
	else
	    flag->size_width++;
	if (dec >= 0)
	    flag->size_width++;
	*return_value += ft_print_format_left(flag, size, dec);
}

void ft_print_u_dec(va_list ap, t_flag *flag, int *return_value)
{
    unsigned int u_dec;
    int size;

    if (flag->dot == 1)
        flag->zero = 0;
    u_dec = va_arg(ap, unsigned int);
    size = ft_chek_u(u_dec);
    *return_value += ft_print_format(*flag, size, u_dec);
    if (u_dec != 0 || flag->dot == 0 || flag->count_simbol != 0)
        *return_value += ft_putnbr_u(u_dec);
    else
        flag->size_width++;
    flag->size_width++;
    *return_value += ft_print_format_left(flag, size, 1);
}

void ft_print_hex(va_list ap, char fmt, t_flag *flag, int *return_value)
{
	int size;
	char *hex;
	unsigned int u_dec;

	u_dec = va_arg(ap, unsigned int);
	ft_puthex(fmt, u_dec, &hex);
	size = ft_strlen(hex);
	if (flag->dot == 1 && flag->count_simbol == 0 && u_dec == 0)
		size = 0;
	*return_value += ft_print_format(*flag, size, 1);
	flag->size_width++;
	*return_value += ft_putstr(hex, size);
	*return_value += ft_print_format_left(flag, size, 1);
	if (hex != NULL)
		free(hex);
}

void ft_print_pointer(va_list ap, t_flag *flag, int *return_value)
{
    int size;
    char *hex;
    unsigned long long int ull_dec;

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
    *return_value += ft_print_format_left(flag, size, 1);
    if (hex != NULL)
        free(hex);
}

void ft_print_char(va_list ap, t_flag *flag, int *return_value)
{
	char c;

	flag->zero = 0;
	flag->dot = 0;
	flag->count_simbol = 0;
	c = (char)va_arg(ap, int);
	ft_print_format(*flag, 1, 1);
	flag->size_width++;
	*return_value += ft_putchar(c);
	*return_value += ft_print_format_left(flag, 1, 1);
}

void ft_print_str(va_list ap, t_flag *flag, int *return_value)
{
    char *str;
    int size;

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

void ft_print_procent(t_flag *flag, int *return_value)
{
	flag->dot = 0;
	flag->count_simbol = 0;
	*return_value += ft_print_format(*flag, 1, 1);
	flag->size_width++;
	*return_value += ft_putchar('%');
	*return_value += ft_print_format_left(flag, 1, 1);
}

int ft_print_type(va_list ap, char fmt, t_flag *flag)
{
	int return_value;

	return_value = 0;
	if (fmt == 'd' || fmt == 'i')
		ft_print_dec(ap, flag, &return_value);
    if (fmt == 'u')
        ft_print_u_dec(ap, flag, &return_value);
	if (fmt == 'x' || fmt == 'X')
		ft_print_hex(ap, fmt, flag, &return_value);
    if (fmt == 'p')
        ft_print_pointer(ap, flag, &return_value);
	if (fmt == 'c')
		ft_print_char(ap, flag, &return_value);
    if (fmt == 's')
        ft_print_str(ap, flag, &return_value);
	if (fmt == '%')
		ft_print_procent(flag, &return_value);
	return (return_value);
}

void ft_check_format(va_list ap, const char *fmt, int i, int *return_value)
{
	t_flag flag;

	flag.dot = 0;
	flag.zero = 0;
	flag.minus = 0;
	flag.size_width = 0;
	flag.count_simbol = 0;
	while (fmt[i++] != '\0')
	{
		if (fmt[i] == '-')
			flag.minus = 1;
		if (fmt[i] == '0' && fmt[i - 1] == '%')
			flag.zero = 1;
		if (fmt[i] == '.')
			flag.dot = 1;
		if ((ft_isdigit(fmt[i]) || fmt[i] == '*') && flag.dot == 0 && flag.size_width == 0)
			chek_size_flags(ap, fmt, &flag.size_width, &i);
		if ((ft_isdigit(fmt[i]) || fmt[i] == '*') && flag.dot == 1 && flag.count_simbol == 0)
			chek_size_flags(ap, fmt, &flag.count_simbol, &i);
		if (fmt[i] == 'd' || fmt[i] == 'i' || fmt[i] == 'u' || fmt[i] == 'x' || fmt[i] == 'X' || fmt[i] == 'p' || fmt[i] == 's' || fmt[i] == 'c' || fmt[i] == '%')
		{
			*return_value += ft_print_type(ap, fmt[i], &flag);
			break;
		}
	}
}

int ft_printf(const char *fmt, ...)
{
	va_list ap;
	int i;
	int count;
	int return_value;

	i = 0;
	return_value = 0;
	va_start(ap, fmt);
	while (fmt[i] != '\0')
	{
		count = 0;
		if (fmt[i] == '%' && (count = ft_check_specifier(fmt + i)) > 0)
		{
			ft_check_format(ap, fmt, i, &return_value);
			i += count - 1;
		}
		if (fmt[i] != '%' && count == 0)
			return_value += ft_putchar(fmt[i]);
		i++;
	}
	return (return_value);
}
