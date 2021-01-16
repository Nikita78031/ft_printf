/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwanetta <dwanetta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 16:57:02 by dwanetta          #+#    #+#             */
/*   Updated: 2021/01/16 20:23:31 by dwanetta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_check_specifier(const char *fmt)
{
	int		i;
	int		j;
	char	*flags;

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

void	chek_size_flags(va_list ap, const char *fmt, int *size, int *i)
{
	while (fmt[*i] != '\0')
	{
		if (fmt[*i] == '.')
		{
			*i -= 1;
			break ;
		}
		if (fmt[*i + 1] == '-')
			break ;
		if (fmt[*i] == '*')
		{
			*size = va_arg(ap, int);
			break ;
		}
		else if (fmt[*i] != '0')
		{
			*size = ft_atoi(fmt + *i);
			break ;
		}
		*i += 1;
	}
}

int		ft_print_type(va_list ap, char fmt, t_flag *flag)
{
	int	return_value;

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

void	ft_check_format(va_list ap, const char *fmt, int i, int *return_value)
{
	t_flag	flag;

	ft_flag_init(&flag);
	while (fmt[i++] != '\0')
	{
		if (fmt[i] == '-')
			flag.minus = 1;
		if (fmt[i] == '0' && fmt[i - 1] == '%')
			flag.zero = 1;
		if (fmt[i] == '.')
			flag.dot = 1;
		if ((ft_isdigit(fmt[i]) || fmt[i] == '*')
		&& flag.dot == 0 && flag.size_width == 0)
			chek_size_flags(ap, fmt, &flag.size_width, &i);
		if ((ft_isdigit(fmt[i]) || fmt[i] == '*')
		&& flag.dot == 1 && flag.count_simbol == 0)
			chek_size_flags(ap, fmt, &flag.count_simbol, &i);
		if (fmt[i] == 'd' || fmt[i] == 'i' || fmt[i] == 'u'
		|| fmt[i] == 'x' || fmt[i] == 'X' || fmt[i] == 'p'
		|| fmt[i] == 's' || fmt[i] == 'c' || fmt[i] == '%')
		{
			*return_value += ft_print_type(ap, fmt[i], &flag);
			break ;
		}
	}
}

int		ft_printf(const char *fmt, ...)
{
	va_list	ap;
	int		i;
	int		count;
	int		return_value;

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
