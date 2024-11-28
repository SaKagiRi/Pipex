/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knakto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 21:59:38 by knakto            #+#    #+#             */
/*   Updated: 2024/09/06 21:44:17 by knakto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kml.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*alloc;
	size_t	i;

	if ((count >= SIZE_MAX && size >= SIZE_MAX)
		|| ((ssize_t)count && (ssize_t)size < 0)
		|| (ssize_t)count * (ssize_t)size < 0)
		return (NULL);
	i = count * size;
	alloc = malloc(i);
	if (alloc == NULL)
		return (NULL);
	while (i > 0)
	{
		*(char *)(alloc + (i - 1)) = '\0';
		i--;
	}
	return (alloc);
}
