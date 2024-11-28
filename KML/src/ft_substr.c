/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knakto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 00:53:32 by knakto            #+#    #+#             */
/*   Updated: 2024/09/04 11:24:19 by knakto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kml.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*dst;

	i = 0;
	while (*(s + i))
		i++;
	if (start > i)
		len = 0;
	if (len > (i - start))
		len = (i - start);
	dst = (char *)malloc(sizeof(char) * (len + 1));
	if (dst == NULL)
		return (NULL);
	i = 0;
	while (len > i)
	{
		*(dst + i) = *(s + (start + i));
		i++;
	}
	*(dst + i) = '\0';
	return (dst);
}
