/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knakto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 01:45:25 by knakto            #+#    #+#             */
/*   Updated: 2024/09/07 22:44:42 by knakto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kml.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	len;

	if (!dst || !src)
		return (0);
	i = 0;
	j = 0;
	len = 0;
	while (*(dst + i) && i < size)
		i++;
	if (size < i)
		return (len + size);
	while (*(src + j) && (i + j + 1) < size)
	{
		*(dst + i + j) = *(src + j);
		j++;
	}
	if (i < size)
		*(dst + i + j) = '\0';
	while (*(src + len))
		len++;
	return (i + len);
}
