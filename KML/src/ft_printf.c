/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knakto <knakto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 23:04:01 by knakto            #+#    #+#             */
/*   Updated: 2024/11/17 21:59:17 by knakto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kml.h"

static int	ft_putnbrs(unsigned long nbr, int len, unsigned int base, char *c)
{
	if ((int)nbr < 0 && base == 10)
	{
		len += write(1, "-", 1);
		nbr *= -1;
	}
	if (base == 11)
		base = 10;
	if (nbr >= base)
		len += ft_putnbrs(nbr / base, 0, base, c);
	len += write(1, &c[nbr % base], 1);
	return (len);
}

static int	ft_putptr(unsigned long nbr)
{
	int	len;

	if (!nbr)
		return (write(1, "(nil)", 5));
	len = write(1, "0x", 2);
	return (len + ft_putnbrs((long)nbr, 0, 16, "0123456789abcdef"));
}

static int	ft_puttext(const char *str)
{
	size_t	len;

	len = 0;
	if (!str)
		return (write(1, "(null)", 6));
	while (*(str + len))
		len++;
	return (write(1, str, len));
}

static int	ft_check(const char c, va_list arg)
{
	int	len;
	int	a;

	len = 0;
	if (c == 'c')
	{
		a = va_arg(arg, int);
		return (write(1, &a, 1));
	}
	else if (c == 's')
		len += ft_puttext(va_arg(arg, const char *));
	else if (c == 'p')
		len += ft_putptr(va_arg(arg, unsigned long));
	else if (c == 'd' || c == 'i')
		len += ft_putnbrs(va_arg(arg, int), 0, 10, "0123456789");
	else if (c == 'u')
		len += ft_putnbrs(va_arg(arg, unsigned int), 0, 11, "0123456789");
	else if (c == 'x')
		len += ft_putnbrs(va_arg(arg, unsigned int), 0, 16, "0123456789abcdef");
	else if (c == 'X')
		len += ft_putnbrs(va_arg(arg, unsigned int), 0, 16, "0123456789ABCDEF");
	else if (c == '%')
		len += write(1, "%", 1);
	return (len);
}

int	pnf(const char *str, ...)
{
	int		temp;
	int		len;
	va_list	arg;

	len = 0;
	temp = 0;
	if (str == NULL)
		return (-1);
	va_start(arg, str);
	if (*str == '\0')
		return (0);
	while (*str)
	{
		if (*str == '%')
			temp = ft_check(*++str, arg);
		else
			temp = write(1, str, 1);
		if (len == -1)
			return (-1);
		len += temp;
		str++;
	}
	va_end(arg);
	return (len);
}
