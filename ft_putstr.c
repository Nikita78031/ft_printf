/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwanetta <dwanetta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 15:27:16 by dwanetta          #+#    #+#             */
/*   Updated: 2020/11/03 21:46:11 by dwanetta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_strlen(const char *str)
{
    int	i;

    i = 0;
    while (str[i] != '\0')
        i++;
    return (i);
}

/*int	ft_putstr(char *s, int flag)
{
	int size;
	int return_value;

    return_value = 0;
	if (s != NULL)
	{
	    if (flag == 0)
		    size = ft_strlen(s);
	    else
	        size = flag;
        return_value = write(0, s, size);
	}
	else
        return_value = write(0, "(null)", 6);
    return (return_value);
}*/

int	ft_putstr(char *s, int flag)
{
    int i;
    int return_value;

    return_value = 0;
    i = 0;
    if (flag == -1)
    {
        while (s[i] != '\0')
        {
            return_value += ft_putchar(s[i]);
            i++;
        }
    }
    else
    {
        while (i != flag)
        {
            return_value += ft_putchar(s[i]);
            i++;
        }
    }
    return (return_value);
}