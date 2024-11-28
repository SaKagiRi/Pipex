/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argstr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knakto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 23:42:23 by knakto            #+#    #+#             */
/*   Updated: 2024/11/17 15:31:22 by knakto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/kml.h"

//don't touch it please T^T
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
	*(dest + i + j) = '\n';
	*(dest + i + j + 1) = '\0';
}

char	*strjoin_nl(char *s1, char *s2)
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
	if (!s1 && !s2)
		return (NULL);
	if (!s1 && s2)
		return (s2);
	if (!s2 && s1)
		return (s1);
	create_malloc = len + len2;
	join = (char *)malloc((sizeof(char) * (create_malloc + 2)));
	if (join == NULL)
		return (NULL);
	cpy_and_cat(join, s1, s2);
	free(s1);
	return (join);
}

static char	*sub(char *find, char **n, char *str, int i)
{
	size_t	j;
	size_t	k;

	j = 0;
	while (n[i][j])
	{
		k = 0;
		while (find[k] == n[i][j + k] && find[k])
			if (!find[++k])
				return (strjoin_nl(str, n[i]));
		j++;
	}
	return (str);
}

char	*argstr(char *find, char **n)
{
	size_t	i;
	char	*str;

	if (!find || !n)
		return (NULL);
	i = 0;
	str = ft_strdup("");
	while (n[i])
	{
		if (!*find)
			str = strjoin_nl(str, n[i++]);
		else
			str = sub(find, n, str, i++);
	}
	return (str);
}
