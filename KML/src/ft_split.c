/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knakto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 23:12:48 by knakto            #+#    #+#             */
/*   Updated: 2024/11/18 13:58:23 by knakto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kml.h"

static size_t	count_word(char *s, char c)
{
	size_t	count;
	size_t	i;
	int		add;

	count = 0;
	i = 0;
	add = 0;
	while (*(s + i))
	{
		if (*(s + i) == c)
			add = 0;
		else if (add == 0)
		{
			add++;
			count++;
		}
		i++;
	}
	return (count);
}

static char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	if (dest == NULL || src == NULL)
		return (NULL);
	while (n > 0 && *(src + i) != '\0')
	{
		*(dest + i) = *(src + i);
		i++;
		n--;
	}
	*(dest + i) = '\0';
	return (dest);
}

char	**free_split(char **alloc)
{
	size_t	i;

	i = 0;
	while (*(alloc + i) != NULL)
	{
		free(*(alloc + i));
		i++;
	}
	free(alloc);
	return (NULL);
}

static char	**ft_alloc(char **str, char *s, char c, size_t count)
{
	size_t	i;
	size_t	start;
	size_t	len;

	i = 0;
	start = 0;
	while (i < count)
	{
		len = 0;
		while (*(s + start) == c)
			start++;
		while (*(s + (start + len)) && *(s + (start + len)) != c)
			len++;
		*(str + i) = (char *)malloc(sizeof(char) * (len + 1));
		if (*(str + i) == NULL)
			return (free_split(str));
		ft_strncpy(*(str + i), s + start, len);
		start += len;
		i++;
	}
	*(str + i) = NULL;
	return (str);
}

char	**ft_split(const char *s, char c)
{
	size_t	count;
	char	**str;

	if (!s)
		return (NULL);
	count = count_word((char *)s, c);
	if (count == 1)
	{
		str = malloc(sizeof(char *) * 3);
		if (!str)
			return (NULL);
		str[0] = ft_strdup(s);
		str[1] = NULL;
		return (str);
	}
	str = (char **)malloc(sizeof(char *) * (count + 2));
	if (str == NULL)
		return (NULL);
	str = ft_alloc(str, (char *)s, c, count);
	*(str + count + 1) = NULL;
	return (str);
}
