/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knakto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 11:27:53 by knakto            #+#    #+#             */
/*   Updated: 2024/11/17 04:33:10 by knakto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kml.h"

static void	cpy_and_cat(char *dest, const char *s1, const char *s2)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (*(s1 + i))
	{
		*(dest + i) = *(s1 + i);
		i++;
	}
	while (*(s2 + j))
	{
		*(dest + i + j) = *(s2 + j);
		j++;
	}
	*(dest + i + j) = '\0';
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	len;
	size_t	len2;
	size_t	create_malloc;
	char	*join;

	len = 0;
	len2 = 0;
	while (*(s1 + len))
		len++;
	while (*(s2 + len2))
		len2++;
	if (len == 0 && len2 == 0)
		return (NULL);
	if (len == 0 && len2 != 0)
		return (s2);
	if (len != 0 && len2 == 0)
		return (s1);
	create_malloc = len + len2;
	join = (char *)malloc((sizeof(char) * (create_malloc + 1)));
	if (join == NULL)
		return (NULL);
	cpy_and_cat(join, s1, s2);
	return (join);
}
