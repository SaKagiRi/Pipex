/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nascii.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knakto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 20:54:31 by knakto            #+#    #+#             */
/*   Updated: 2024/11/01 20:54:58 by knakto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

static	char	*decode_nscii(char *str)
{
	char	*dest;
	int	len;
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (*(str + len))
		len++;
	dest = malloc(sizeof(char) * (len + 1));
	while (str[j])
	{
		if (i == 27)
			i = 1;
		if ((str[j] >= '0' && str[j] <= '9' && str[j] + i <= '9')
			|| (str[j] >= 'a' && str[j] <= 'z' && str[j] + i <= 'z'))
			dest[j] = str[j] + i;
		else if (str[j] >= '0' && str[j] <= '9')
			dest[j] = ((str[j] + i + 1) - '9') + 'a';
		else if (str[j] >= 'a' && str[j] <= 'z')
			dest[j] = 'Z' - ((str[j] + i + 1) - 'z');
		else if (str[j] >= 'A' && str[j] <= 'Z' && str[j] - i >= 'A')
			dest[j] = str[j] - i;
		else if (str[j] >= 'A' && str[j] <= 'Z')
			dest[j] = ('A' - (str[j] - i + 1)) + '0';
		else
			dest[j] = str[j];
		i++;
		j++;
	}
	dest[j] = '\0';
	return (dest);
}

static	char	*encode_nscii(char *str)
{
	char	*dest;
	int	len;
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (*(str + len))
		len++;
	dest = malloc(sizeof(char) * (len + 1));
	while (str[j])
	{
		if (i == 27)
			i = 1;
		if ((str[j] >= '0' && str[j] <= '9' && str[j] - i >= '0')
				|| (str[j] >= 'a' && str[j] <= 'z' && str[j] - i >= 'a'))
			dest[j] = str[j] - i;
		else if (str[j] >= '0' && str[j] <= '9')
			dest[j] = '0' - (str[j] - i + 1) + 'A';
		else if (str[j] >= 'a' && str[j] <= 'z')
			dest[j] = '9' - ('a' - (str[j] - i + 1));
		else if (str[j] >= 'A' && str[j] <= 'Z' && str[j] + i <= 'Z')
			dest[j] = str[j] + i;
		else if (str[j] >= 'A' && str[j] <= 'Z')
			dest[j] = 'z' - ((str[j] + i + 1) - 'Z');
		else
			dest[j] = str[j];
		i++;
		j++;
	}
	dest[j] = '\0';
	return (dest);
}

int	main(int c, char **v)
{
	char	*str;

	if (c != 3)
		return (printf("./nscii [word] [option]\n	--option  1  encoding\n	      	  2  decoding"));
	if (v[2][0] == '1')
		printf("%s", encode_nscii(v[1]));
	else
		printf("%s", decode_nscii(v[1]));
	return (0);
}
