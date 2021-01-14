/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwanetta <dwanetta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 16:20:14 by dwanetta          #+#    #+#             */
/*   Updated: 2021/01/15 01:19:23 by dwanetta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_FT_H
#define PRINTF_FT_H

#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>

typedef struct	s_flag
{
	int			dot;
	int			zero;
	int			minus;
	int			size_width;
	int			count_simbol;
}				t_flag;

int		ft_printf(const char *format, ...);
int		ft_isdigit(int c);
int		ft_atoi(const char *str);
int		ft_putchar(char c);
int		ft_putnbr_u(unsigned int n);
int		ft_putnbr(int n, int flag);
int		ft_chek_u(unsigned int tmp);
int		ft_chek(int tmp);
void	ft_puthex(char fmt, unsigned int u_dec, char **hex);
int		ft_strlen(const char *str);
int		ft_putstr(char *s, int flag);
void	ft_puthex_pointer(unsigned long long int ull_dec, char **hex);

#endif
