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

void chek_size_flags (va_list ap, const char *fmt, int *size, int *i)
{
    while (fmt[*i] != '\0')
    {
        if (fmt[*i] == '.')
        {
            *i -= 1;
            break;
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

int ft_print_format(t_flag flag, int size, long int value)
{
    int return_value;
    char symbol;

    return_value = 0;
    if (value == 0 && flag.dot != 0 && flag.count_simbol == 0)
        flag.size_width += 1;
    if (flag.zero == 0 || flag.count_simbol > 0)// sandiadad
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

void ft_print_dec(va_list ap, char fmt, t_flag *flag, int *return_value)
{
    int dec;
    unsigned int u_dec;
    int size;

    dec = 0;
    if (fmt == 'u')
    {
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
    }
    else
    {
        dec = va_arg(ap, int);
        size = ft_chek(dec);
        *return_value += ft_print_format(*flag, size, dec);
        if (dec != 0 || flag->dot == 0 || flag->count_simbol != 0)
            *return_value += ft_putnbr(dec, 1);
        else
            flag->size_width++;
        if (dec >= 0)
            flag->size_width++;
    }
    *return_value += ft_print_format_left(flag, size, dec);
}

void ft_print_hex(va_list ap, char fmt, t_flag *flag, int *return_value)
{
    int size;
    char *hex;
    unsigned int u_dec;
    unsigned long long int ull_dec;

    ull_dec = 0;
    u_dec = 0;
    if (fmt == 'x' || fmt == 'X')
    {
        u_dec = va_arg(ap, unsigned int);
        ft_puthex(fmt, u_dec, &hex);
    }
    else
    {
        ull_dec = va_arg(ap, unsigned long long int);
        ft_puthex_pointer(ull_dec, &hex);
        if (flag->size_width > 0)
            flag->size_width -=2;
        else if (flag->size_width < 0 )
            flag->size_width +=2;
    }
    size = ft_strlen(hex);
    if (flag->dot == 1 && flag->count_simbol == 0 && u_dec == 0 && ull_dec == 0)
        size = 0;
    *return_value += ft_print_format(*flag, size, 1);
    if (fmt == 'p')
    {
        *return_value += ft_putchar('0');
        *return_value += ft_putchar('x');
    }
    flag->size_width++;
    *return_value += ft_putstr(hex, size);
    *return_value += ft_print_format_left(flag, size, 1);
    if (hex != NULL)
        free(hex);
}

void ft_print_char(va_list ap, char fmt, t_flag *flag, int *return_value)
{
    char *str;
    int size;
    char c;

    flag->zero = 0;
    if (fmt == 'c')
    {
        flag->zero = 0;
        flag->dot = 0;
        flag->count_simbol = 0;
        c = (char)va_arg(ap, int);
        ft_print_format(*flag, 1, 1);
        flag->size_width++;
        *return_value += ft_putchar(c);
        *return_value += ft_print_format_left(flag, 1, 1);
    }
    else
    {
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
    if (fmt == 'd' || fmt == 'i' || fmt == 'u')
        ft_print_dec(ap, fmt, flag, &return_value);
    if (fmt == 'x' || fmt == 'X' || fmt == 'p')
        ft_print_hex(ap, fmt, flag, &return_value);
    if (fmt == 'c' || fmt == 's')
        ft_print_char(ap, fmt, flag, &return_value);
    if (fmt == '%')
        ft_print_procent(flag, &return_value);
    return (return_value);
}

void ft_check_format(va_list ap, const char *fmt, int i, int *return_value)
{
    t_flag  flag;

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
        if(fmt[i] == 'd' || fmt[i] == 'i' || fmt[i] == 'u' || fmt[i] == 'x'
        || fmt[i] == 'X' || fmt[i] == 'p' || fmt[i] == 's' || fmt[i] == 'c' || fmt[i] == '%')
        {
            *return_value += ft_print_type(ap, fmt[i], &flag);
            break ;
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


/*int	main()
{

    int a;
    char *b;
    a = 2;
    b = "abcd";
    printf("     %d\n",  ft_printf("%082.u" ,4183054859u));
    printf("\n");
    printf("     %d\n",     printf("%% *.5i 42 == |%*.5i|", 4, 42));*/

/*
    int		res;
    int		ft_res;

    printf("-----------------   test char %%   -----------------\n");
    printf("   printf ----- %-10.5%|\n", 'h');
    ft_printf("ft_printf ----- %-10.5%|\n", 'h');
    printf("   printf ----- %020.5%|\n", 'h');
    ft_printf("ft_printf ----- %020.5%|\n", 'h');
    printf("-----------------   test char %% end   -----------------\n\n\n");


    printf("-----------------   test char start   -----------------\n");
    res = printf("   printf ----- %04.5c|\n", 'h');
    ft_res = ft_printf("ft_printf ----- %04.5c|\n", 'h');
    printf("res = %d          ft_res = %d\n", res, ft_res);
    printf("-----------------   test char end   -----------------\n\n\n");


    printf("-----------------   test string start   -----------------\n");
    printf("   printf ----- %0*s\n", 25, "hello world!");
    ft_printf("ft_printf ----- %0*s\n", 25, "hello world!");
    printf("res = %d          ft_res = %d\n", res, ft_res);
    printf("**************************************************\n");
    res = printf("   printf ----- %-10.3s|\n", "hello world!");
    ft_res = ft_printf("ft_printf ----- %-10.3s|\n", "hello world!");
    printf("res = %d          ft_res = %d\n", res, ft_res);
    printf("**************************************************\n");
    res = printf("   printf ----- %010.3s\n", "hello world!");
    ft_res = ft_printf("ft_printf ----- %010.3s\n", "hello world!");
    printf("res = %d          ft_res = %d\n", res, ft_res);
    printf("**************************************************\n");
    res = printf("   printf ----- %20.s\n", "hello world!");
    ft_res = ft_printf("ft_printf ----- %20.s\n", "hello world!");
    printf("res = %d          ft_res = %d\n", res, ft_res);
    printf("**************************************************\n");
    res = printf("   printf ----- |%20.s|\n", 0);
    ft_res = ft_printf("ft_printf ----- |%20.s|\n", 0);
    printf("-----------------   test string end   -----------------\n\n\n");


    printf("-----------------   test pointer start   -----------------\n");
    char *s = malloc(1);
    res = printf("   printf ----- %p\n", NULL);
    ft_res = ft_printf("ft_printf ----- %p\n", NULL);
    printf("res = %d          ft_res = %d\n", res, ft_res);
    printf("**************************************************\n");
    res = printf("   printf ----- %p\n", &s);
    ft_res = ft_printf("ft_printf ----- %p\n", &s);
    printf("res = %d          ft_res = %d\n", res, ft_res);
    printf("**************************************************\n");
    res = printf("   printf ----- %20p\n", &s);
    ft_res = ft_printf("ft_printf ----- %20p\n", &s);
    printf("res = %d          ft_res = %d\n", res, ft_res);
    printf("**************************************************\n");
    res = printf("   printf ----- %020p\n", &s);
    ft_res = ft_printf("ft_printf ----- %020p\n", &s);
    printf("res = %d          ft_res = %d\n", res, ft_res);
    printf("**************************************************\n");
    res = printf("   printf ----- %020p\n", NULL);
    ft_res = ft_printf("ft_printf ----- %020p\n", NULL);
    printf("res = %d          ft_res = %d\n", res, ft_res);
    printf("**************************************************\n");
    res = printf("   printf ----- %35.55p\n", &s);
    ft_res = ft_printf("ft_printf ----- %35.55p\n", &s);
    printf("res = %d          ft_res = %d\n", res, ft_res);
    printf("**************************************************\n");
    res = printf("   printf ----- %035.15p\n", &s);
    ft_res = ft_printf("ft_printf ----- %035.15p\n", &s);
    printf("res = %d          ft_res = %d\n", res, ft_res);
    printf("**************************************************\n");
    res = printf("   printf ----- %35.5p\n", &s);
    ft_res = ft_printf("ft_printf ----- %35.5p\n", &s);
    printf("res = %d          ft_res = %d\n", res, ft_res);
    printf("**************************************************\n");
    res = printf("   printf ----- %0*.15p\n", 40, &s);
    ft_res = ft_printf("ft_printf ----- %0*.15p\n", 40, &s);
    printf("res = %d          ft_res = %d\n", res, ft_res);
    printf("**************************************************\n");
    res = printf("   printf ----- %05p\n", NULL);
    ft_res = ft_printf("ft_printf ----- %05p\n", NULL);
    printf("res = %d          ft_res = %d\n", res, ft_res);
    printf("**************************************************\n");
    res = printf("   printf ----- %5p\n", NULL);
    ft_res = ft_printf("ft_printf ----- %5p\n", NULL);
    printf("res = %d          ft_res = %d\n", res, ft_res);
    printf("**************************************************\n");
    res = printf("   printf ----- %70p\n", &s);
    ft_res = ft_printf("ft_printf ----- %70p\n", &s);
    printf("res = %d          ft_res = %d\n", res, ft_res);
    printf("**************************************************\n");
    res = printf("   printf ----- |%-70p|\n", &s);
    ft_res = ft_printf("ft_printf ----- |%-70p|\n", &s);
    printf("res = %d          ft_res = %d\n", res, ft_res);
    printf("-----------------   test pointer end   -----------------\n\n\n");



    printf("-----------------   test digit start   -----------------\n");
    printf("********************* test №1 *****************\n");
    res = printf("   printf ----- %7.7d\n", -12345);
    ft_res = ft_printf("ft_printf ----- %7.7d\n", -12345);
    printf("res = %d          ft_res = %d\n", res, ft_res);
    printf("********************* test №2 *****************\n");
    res = printf("   printf ----- %-7.7d\n", -12345);
    ft_res = ft_printf("ft_printf ----- %7.7d\n", -12345);
    printf("res = %d          ft_res = %d\n", res, ft_res);
    printf("********************* test №3 *****************\n");
    res = printf("   printf ----- %70d\n", 142);
    ft_res = ft_printf("ft_printf ----- %70d\n", 142);
    printf("res = %d          ft_res = %d\n", res, ft_res);
    printf("********************* test №4 *****************\n");
    res = printf("   printf ----- %.4d\n", 142);
    ft_res = ft_printf("ft_printf ----- %.4d\n", 142);
    printf("res = %d          ft_res = %d\n", res, ft_res);
    printf("********************* test №5 *****************\n");
    res = printf("   printf ----- %5.4d\n", 142);
    ft_res = ft_printf("ft_printf ----- %5.4d\n", 142);
    printf("res = %d          ft_res = %d\n", res, ft_res);
    printf("********************* test №6 *****************\n");
    res = printf("   printf ----- |%15.4d|\n", 142);
    ft_res = ft_printf("ft_printf ----- |%15.4d|\n", 142);
    printf("res = %d          ft_res = %d\n", res, ft_res);
    printf("********************* test №7 *****************\n");
    res = printf("   printf ----- |%-15.4d|\n", 142);
    ft_res = ft_printf("ft_printf ----- |%-15.4d|\n", 142);
    printf("res = %d          ft_res = %d\n", res, ft_res);
    printf("********************* test №8 *****************\n");
    res = printf("   printf ----- |%-15.25d|\n", -142);
    ft_res = ft_printf("ft_printf ----- |%-15.25d|\n", -142);
    printf("res = %d          ft_res = %d\n", res, ft_res);
    printf("********************* test №9 *****************\n");
    res = printf("   printf ----- |%-15d|\n", -33333);
    ft_res = ft_printf("ft_printf ----- |%-15d|\n", -33333);
    printf("res = %d          ft_res = %d\n", res, ft_res);
    printf("********************* test №10 *****************\n");
    res = printf("   printf ----- |%15d|\n", -22222222);
    ft_res = ft_printf("ft_printf ----- |%15d|\n", -22222222);
    printf("res = %d          ft_res = %d\n", res, ft_res);
    printf("********************* test №11 *****************\n");
    res = printf("   printf ----- |%-.25d|\n", -8765);
    ft_res = ft_printf("ft_printf ----- |%-.25d|\n", -8765);
    printf("res = %d          ft_res = %d\n", res, ft_res);
    printf("********************* test №12 *****************\n");
    res = printf("   printf ----- |%-35.25d|\n", -142);
    ft_res = ft_printf("ft_printf ----- |%-35.25d|\n", -142);
    printf("res = %d          ft_res = %d\n", res, ft_res);
    printf("********************* test №13 *****************\n");
    res = printf("   printf ----- |%.6d|\n", -6);
    ft_res = ft_printf("ft_printf ----- |%.6d|\n", -6);
    printf("res = %d          ft_res = %d\n", res, ft_res);
    printf("**************************************************\n");
    res = printf("   printf ----- |%07d|\n", -54);
    ft_res = ft_printf("ft_printf ----- |%07d|\n", -54);
    printf("res = %d          ft_res = %d\n", res, ft_res);
    printf("********************* test №14 *****************\n");
    res = printf("   printf ----- |%07d|\n", 54);
    ft_res = ft_printf("ft_printf ----- |%07d|\n", 54);
    printf("res = %d          ft_res = %d\n", res, ft_res);
    printf("********************* test №1 *****************\n");
    res = printf("   printf ----- |%03d|\n", 0);
    ft_res = ft_printf("ft_printf ----- |%03d|\n", 0);
    printf("res = %d          ft_res = %d\n", res, ft_res);
    printf("********************* test №15 *****************\n");
    res = printf("   printf ----- |%10.5d|\n", -216);
    ft_res = ft_printf("ft_printf ----- |%10.5d|\n", -216);
    printf("res = %d          ft_res = %d\n", res, ft_res);
    printf("********************* test №16 *****************\n");
    res = printf("   printf ----- |%8.5d|\n", 34);
    ft_res = ft_printf("ft_printf ----- |%8.5d|\n", 34);
    printf("res = %d          ft_res = %d\n", res, ft_res);
    printf("********************* test №17 *****************\n");
    res = printf("   printf ----- |%8.3d|\n", -8434);
    ft_res = ft_printf("ft_printf ----- |%8.3d|\n", -8434);
    printf("res = %d          ft_res = %d\n", res, ft_res);
    printf("********************* test №18 *****************\n");
    res = printf("   printf ----- |%-8.5d|\n", 0);
    ft_res = ft_printf("ft_printf ----- |%-8.5d|\n", 0);
    printf("res = %d          ft_res = %d\n", res, ft_res);
    printf("********************* test №19 *****************\n");
    res = printf("   printf ----- |%-8.3d|\n", 1230);
    ft_res = ft_printf("ft_printf ----- |%-8.3d|\n", 1230);
    printf("********************* test №20 *****************\n");
    res = printf("   printf ----- |%8.d|\n", 0);
    ft_res = ft_printf("ft_printf ----- |%8.d|\n", 0);
    printf("res = %d          ft_res = %d\n", res, ft_res);
    printf("-----------------   test digit end   -----------------\n\n\n");



    printf("-----------------   test unsigned start   -----------------\n");
    res = printf("   printf ----- |%u|\n", -2);
    ft_res = ft_printf("ft_printf ----- |%u|\n", -2);
    printf("res = %d          ft_res = %d\n", res, ft_res);
    printf("**************************************************\n");
    res = printf("   printf ----- |%30u|\n", -12342);
    ft_res = ft_printf("ft_printf ----- |%30u|\n", -12342);
    printf("res = %d          ft_res = %d\n", res, ft_res);
    printf("**************************************************\n");
    res = printf("   printf ----- |%-30u|\n", 12342);
    ft_res = ft_printf("ft_printf ----- |%-30u|\n", 12342);
    printf("res = %d          ft_res = %d\n", res, ft_res);
    printf("**************************************************\n");
    res = printf("   printf ----- |%-30.25u|\n", 12342);
    ft_res = ft_printf("ft_printf ----- |%-30.25u|\n", 12342);
    printf("res = %d          ft_res = %d\n", res, ft_res);
    printf("**************************************************\n");
    res = printf("   printf ----- |%-30.45u|\n", 12342);
    ft_res = ft_printf("ft_printf ----- |%-30.45u|\n", 12342);
    printf("res = %d          ft_res = %d\n", res, ft_res);
    printf("**************************************************\n");
    res = printf("   printf ----- |%-30.0u|\n", 0);
    ft_res = ft_printf("ft_printf ----- |%-30.0u|\n", 0);
    printf("res = %d          ft_res = %d\n", res, ft_res);
    printf("-----------------   test unsigned end   -----------------\n\n\n");


    printf("-----------------   test i start   -----------------\n");
    res = printf("   printf ----- |%i|\n", -1);
    ft_res = ft_printf("ft_printf ----- |%i|\n", -1);
    printf("res = %d          ft_res = %d\n", res, ft_res);
    printf("**************************************************\n");
    res = printf("   printf ----- |%i|\n", 0);
    ft_res = ft_printf("ft_printf ----- |%i|\n", 0);
    printf("res = %d          ft_res = %d\n", res, ft_res);
    printf("**************************************************\n");
    res = printf("   printf ----- |%i|\n", 213456712345);
    ft_res = ft_printf("ft_printf ----- |%i|\n", 213456712345);
    printf("res = %d          ft_res = %d\n", res, ft_res);
    printf("**************************************************\n");
    res = printf("   printf ----- |%i|\n", -213456712345);
    ft_res = ft_printf("ft_printf ----- |%i|\n", -213456712345);
    printf("res = %d          ft_res = %d\n", res, ft_res);
    printf("**************************************************\n");
    res = printf("   printf ----- |%023.4i|\n", -213456712345);
    ft_res = ft_printf("ft_printf ----- |%023.4i|\n", -213456712345);
    printf("res = %d          ft_res = %d\n", res, ft_res);
    printf("**************************************************\n");
    res = printf("   printf ----- |%-030.20i|\n", -345);
    ft_res = ft_printf("ft_printf ----- |%-030.20i|\n", -345);
    printf("res = %d          ft_res = %d\n", res, ft_res);
    printf("**************************************************\n");
    printf("-----------------   test i end   -----------------\n\n\n");



    printf("-----------------   test x start   -----------------\n");
    res = printf("   printf ----- |%x|\n", -1);
    ft_res = ft_printf("ft_printf ----- |%x|\n", -1);
    printf("res = %d          ft_res = %d\n", res, ft_res);
    printf("**************************************************\n");
    res = printf("   printf ----- |%x|\n", 21345);
    ft_res = ft_printf("ft_printf ----- |%x|\n", 21345);
    printf("res = %d          ft_res = %d\n", res, ft_res);
    printf("**************************************************\n");
    res = printf("   printf ----- |%10.3x|\n", 123456);
    ft_res = ft_printf("ft_printf ----- |%10.3x|\n", 123456);
    printf("res = %d          ft_res = %d\n", res, ft_res);
    printf("**************************************************\n");
    res = printf("   printf ----- |%20.5x|\n", 3);
    ft_res = ft_printf("ft_printf ----- |%20.5x|\n", 3);
    printf("res = %d          ft_res = %d\n", res, ft_res);
    printf("**************************************************\n");
    res = printf("   printf ----- |%5.20x|\n", 3);
    ft_res = ft_printf("ft_printf ----- |%5.20x|\n", 3);
    printf("res = %d          ft_res = %d\n", res, ft_res);
    printf("**************************************************\n");
    res = printf("   printf ----- |%-020.5x|\n", 3);
    ft_res = ft_printf("ft_printf ----- |%-020.5x|\n", 3);
    printf("res = %d          ft_res = %d\n", res, ft_res);
    printf("**************************************************\n");
    res = printf("   printf ----- |%020.5x|\n", 0);
    ft_res = ft_printf("ft_printf ----- |%020.5x|\n", 0);
    printf("res = %d          ft_res = %d\n", res, ft_res);
    printf("**************************************************\n");
    res = printf("   printf ----- |%020.x|\n", 0);
    ft_res = ft_printf("ft_printf ----- |%020.x|\n", 0);
    printf("res = %d          ft_res = %d\n", res, ft_res);
    printf("**************************************************\n");
    res = printf("   printf ----- |%020x|\n", 0);
    ft_res = ft_printf("ft_printf ----- |%020x|\n", 0);
    printf("res = %d          ft_res = %d\n", res, ft_res);
    printf("**************************************************\n");
    res = printf("   printf ----- |%05x|\n", 34);
    ft_res = ft_printf("ft_printf ----- |%05x|\n", 34);
    printf("res = %d          ft_res = %d\n", res, ft_res);
    printf("**************************************************\n");
    res = printf("   printf ----- |%7x|\n", 12345621345);
    ft_res = ft_printf("ft_printf ----- |%7x|\n", 12345621345);
    printf("res = %d          ft_res = %d\n", res, ft_res);
    printf("-----------------   test x end   -----------------\n\n\n");



    printf("-----------------   test X start   -----------------\n");
    res = printf("   printf ----- |%X|\n", -1);
    ft_res = ft_printf("ft_printf ----- |%X|\n", -1);
    printf("res = %d          ft_res = %d\n", res, ft_res);
    printf("**************************************************\n");
    res = printf("   printf ----- |%X|\n", 21345);
    ft_res = ft_printf("ft_printf ----- |%X|\n", 21345);
    printf("res = %d          ft_res = %d\n", res, ft_res);
    printf("**************************************************\n");
    res = printf("   printf ----- |%10.3X|\n", 123456);
    ft_res = ft_printf("ft_printf ----- |%10.3X|\n", 123456);
    printf("res = %d          ft_res = %d\n", res, ft_res);
    printf("**************************************************\n");
    res = printf("   printf ----- |%20.5X|\n", 3);
    ft_res = ft_printf("ft_printf ----- |%20.5X|\n", 3);
    printf("res = %d          ft_res = %d\n", res, ft_res);
    printf("**************************************************\n");
    res = printf("   printf ----- |%5.20X|\n", 3);
    ft_res = ft_printf("ft_printf ----- |%5.20X|\n", 3);
    printf("res = %d          ft_res = %d\n", res, ft_res);
    printf("**************************************************\n");
    res = printf("   printf ----- |%-020.5X|\n", 3);
    ft_res = ft_printf("ft_printf ----- |%-020.5X|\n", 3);
    printf("res = %d          ft_res = %d\n", res, ft_res);
    printf("**************************************************\n");
    res = printf("   printf ----- |%020.5X|\n", 0);
    ft_res = ft_printf("ft_printf ----- |%020.5X|\n", 0);
    printf("**************************************************\n");
    res = printf("   printf ----- |%020.X|\n", 0);
    ft_res = ft_printf("ft_printf ----- |%020.X|\n", 0);
    printf("res = %d          ft_res = %d\n", res, ft_res);
    printf("**************************************************\n");
    res = printf("   printf ----- |%020X|\n", 0);
    ft_res = ft_printf("ft_printf ----- |%020X|\n", 0);
    printf("res = %d          ft_res = %d\n", res, ft_res);
    printf("**************************************************\n");
    res = printf("   printf ----- |%05X|\n", 34);
    ft_res = ft_printf("ft_printf ----- |%05X|\n", 34);
    printf("res = %d          ft_res = %d\n", res, ft_res);
    printf("**************************************************\n");
    res = printf("   printf ----- |%7X|\n", 12345621345);
    ft_res = ft_printf("ft_printf ----- |%7X|\n", 12345621345);
    printf("res = %d          ft_res = %d\n", res, ft_res);
    printf("-----------------   test X end   -----------------\n\n\n");



    printf("**************************************************\n");
    res = printf("   printf ----- |%20.5x|\n", 33333);
    ft_res = ft_printf("ft_printf ----- |%20.5x|\n", 33333);
    printf("res = %d          ft_res = %d\n", res, ft_res);
    printf("**************************************************\n");
    res = printf("   printf ----- |%5.20x|\n", 33333);
    ft_res = ft_printf("ft_printf ----- |%5.20x|\n", 33333);
    printf("res = %d          ft_res = %d\n", res, ft_res);
    printf("**************************************************\n");
    res = printf("   printf ----- |%-020.5x|\n", 33333);
    ft_res = ft_printf("ft_printf ----- |%-020.5x|\n", 33333);
    printf("res = %d          ft_res = %d\n", res, ft_res);
    printf("**************************************************\n");
    res = printf("   printf ----- |%-8.5x|\n", 34);
    ft_res = ft_printf("ft_printf ----- |%-8.5x|\n", 34);
    printf("res = %d          ft_res = %d\n", res, ft_res);
    printf("**************************************************\n");
    res = printf("   printf ----- |%2.9p|\n", 1234);
    ft_res = ft_printf("ft_printf ----- |%2.9p|\n", 1234);
    printf("res = %d          ft_res = %d\n", res, ft_res);
    printf("**************************************************\n");
    res = printf("   printf ----- |%20.16p|\n", 1234);
    ft_res = ft_printf("ft_printf ----- |%20.16p|\n", 1234);
    printf("res = %d          ft_res = %d\n", res, ft_res);
    printf("**************************************************\n");
    res = printf("   printf ----- |%15.20p|\n", 1234);
    ft_res = ft_printf("ft_printf ----- |%15.20p|\n", 1234);
    printf("res = %d          ft_res = %d\n", res, ft_res);
    printf("**************************************************\n");
    res = printf("   printf ----- |%5.7p|\n", 1);
    ft_res = ft_printf("ft_printf ----- |%5.7p|\n", 1);
    printf("res = %d          ft_res = %d\n", res, ft_res);
    printf("**************************************************\n");
    res = printf("   printf ----- |%.5p|\n", 0);
    ft_res = ft_printf("ft_printf ----- |%.5p|\n", 0);
    printf("res = %d          ft_res = %d\n", res, ft_res);
    printf("**************************************************\n");
    res = printf("   printf ----- %020p\n", &s);
    ft_res = ft_printf("ft_printf ----- %020p\n", &s);
    printf("res = %d          ft_res = %d\n", res, ft_res);
    printf("**************************************************\n");
    res = printf("   printf ----- |%5|\n");
    ft_res = ft_printf("ft_printf ----- |%5|\n");
    printf("res = %d          ft_res = %d\n", res, ft_res);
    printf("**************************************************\n");
    res = printf("   printf ----- |%5.0| |%s|\n", &s);
    ft_res = ft_printf("ft_printf ----- |%5.0| |%s|\n", &s);
    printf("res = %d          ft_res = %d\n", res, ft_res , "q2er", "123 4324refwa", 123234);
    printf("**************************************************\n");
    res = printf("   printf ----- |%5| |%s|\n", &s);
    ft_res = ft_printf("ft_printf ----- |%5| |%s|\n", &s);
    printf("res = %d          ft_res = %d\n", res, ft_res ,"q2er", "123 4324refwa", 123234);
    res = printf("   printf ----- %", &s);
    ft_res = ft_printf("ft_printf ----- %", &s);
    printf("\nres = %d          ft_res = %d\n", res, ft_res);
    printf("---------------------------------------------------------\n", &s);
    ft_printf("%%%%%%%%d\n", 42);
    printf("%%%%%%%%d\n", 42);
    }*/

/*    return 0;
}*/
