/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knakto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 19:50:58 by knakto            #+#    #+#             */
/*   Updated: 2024/09/06 17:48:49 by knakto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kml.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*temp;
	unsigned char	chr;

	temp = (unsigned char *) s;
	chr = (unsigned char) c;
	while (n > 0)
	{
		*(temp + (n - 1)) = chr;
		n--;
	}
	return (temp);
}
