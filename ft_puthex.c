/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwanetta <dwanetta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 15:34:06 by dwanetta          #+#    #+#             */
/*   Updated: 2020/11/05 18:24:53 by dwanetta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void ft_puthex(char fmt, unsigned int u_dec, char **hex)
{
    char *str;
    unsigned int tmp;
    int i;
    int j;

    i = 1;
    if (fmt == 'x')
        str = "0123456789abcdef";
    else
        str = "0123456789ABCDEF";
    tmp = u_dec;
    while (tmp > 15)
    {
        tmp /= 16;
        i++;
    }
    if ((*hex = (char*)malloc(sizeof(char) * i + 1)) != NULL)
    {
        hex[0][i] = '\0';
        while (i != 0) {
            i--;
            j = (int) (u_dec - (16 * (u_dec / 16)));
            u_dec /= 16;
            hex[0][i] = str[j];
        }
    }
}

void ft_puthex_pointer(unsigned long long int ull_dec, char **hex)
{
    char *str;
    unsigned long long int tmp;
    int i;
    int j;

    i = 1;
    str = "0123456789abcdef";
    tmp = ull_dec;
    while (tmp > 15)
    {
        tmp /= 16;
        i++;
    }
    if ((*hex = (char*)malloc(sizeof(char) * i + 1)) != NULL)
    {
        hex[0][i] = '\0';
        while (i != 0) {
            i--;
            j = (int) (ull_dec - (16 * (ull_dec / 16)));
            ull_dec /= 16;
            hex[0][i] = str[j];
        }
    }
}

