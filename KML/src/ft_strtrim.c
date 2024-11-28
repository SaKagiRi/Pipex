/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knakto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 12:49:59 by knakto            #+#    #+#             */
/*   Updated: 2024/09/04 22:03:14 by knakto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kml.h"

static int	charset(char c, const char *set)
{
	size_t	i;

	i = 0;
	while (*(set + i))
	{
		if (*(set + i) == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	size_t	start;
	size_t	end;
	char	*dest;
	size_t	i;

	if (s1 == NULL)
		return (NULL);
	i = 0;
	start = 0;
	end = 0;
	while (*(s1 + end))
		end++;
	while (*(s1 + start) && charset(*(s1 + start), set))
		start++;
	while (end > start && charset(*(s1 + (end - 1)), set))
		end--;
	dest = (char *)malloc(sizeof(char) * (end - start) + 1);
	if (dest == NULL)
		return (NULL);
	while (start < end)
		*(dest + i++) = *(s1 + start++);
	*(dest + i) = '\0';
	return (dest);
}
/*
#include <stdio.h>

int	main(void)
{
	char *s1 = "  \t \t \n   \n\n\n\t";
 	//char *s2 = "";
 	//char *ret = ft_strtrim(s1, " \n\t")
	printf("%s\n", ft_strtrim(s1, " \t\n"));
}
*/
