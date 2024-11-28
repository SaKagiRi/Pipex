/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knakto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 02:59:10 by knakto            #+#    #+#             */
/*   Updated: 2024/09/05 03:06:54 by knakto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kml.h"

static	size_t	ft_len(int n)
{
	long	nbr;
	size_t	len;

	len = 0;
	nbr = (long)n;
	if (nbr == 0)
		len++;
	if (nbr < 0)
	{
		nbr *= -1;
		len++;
	}
	while (nbr > 0)
	{
		nbr /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	long	nl;
	size_t	len;
	char	*str;

	nl = (long)n;
	len = ft_len(n);
	str = (char *)ft_calloc(len + 1, sizeof(char));
	if (str == NULL)
		return (str);
	if (nl < 0)
	{
		*str = '-';
		nl *= -1;
	}
	if (nl == 0)
		*str = '0';
	while (nl > 0 && len > 0)
	{
		*(str + (len - 1)) = (nl % 10) + '0';
		nl /= 10;
		len--;
	}
	return (str);
}
