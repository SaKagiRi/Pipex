/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knakto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 00:29:21 by knakto            #+#    #+#             */
/*   Updated: 2024/09/07 23:14:11 by knakto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kml.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*s;
	unsigned char	*d;

	s = (unsigned char *)src;
	d = (unsigned char *)dest;
	i = 0;
	while (d < s && i < n)
	{
		*(d + i) = *(s + i);
		i++;
	}
	while (d > s && n > 0)
	{
		*(d + (n - 1)) = *(s + (n - 1));
		n--;
	}
	return (dest);
}
