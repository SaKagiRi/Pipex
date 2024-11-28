/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knakto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:36:27 by knakto            #+#    #+#             */
/*   Updated: 2024/11/10 18:19:50 by knakto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kml.h"

static void	read_line(t_var *var)
{
	if (!var->run)
	{
		var->run = (t_lst *)malloc(sizeof(t_lst));
		if (!var->run)
			return ;
		var->run->len = 0;
		var->run->next = NULL;
		var->word = var->run;
	}
	else if (var->eof == 0)
	{
		var->word->next = (t_lst *)malloc(sizeof(t_lst));
		if (!var->word->next)
			return ;
		var->word = var->word->next;
		var->word->len = 0;
		var->word->next = NULL;
	}
	else
		return ;
	var->word->len = read(var->fd, var->word->content, BUFFER_SIZE);
	if (var->word->len == 0)
		var->eof = 1;
}

static void	coppy_line(t_var *var, char *str)
{
	size_t	i;
	t_lst	*temp;

	i = 0;
	while (var->nlb > i)
	{
		str[i++] = var->run->content[var->offset++];
		if (var->offset == var->run->len)
		{
			var->offset = 0;
			temp = var->run;
			var->run = var->run->next;
			free(temp);
		}
	}
}

static void	set_line(t_var *var)
{
	t_lst	*node;
	size_t	i;

	if (!var->run)
		read_line(var);
	node = var->run;
	if (!node || !var->run || var->word->len == (size_t) -1)
		return ;
	while (node->len > 0)
	{
		i = (var->nlb + var->offset) % BUFFER_SIZE;
		if (i > (node->len - 1))
			return ;
		if (node->content[i] == '\n')
		{
			var->nlb += 1;
			return ;
		}
		var->nlb++;
		if (i == BUFFER_SIZE - 1)
		{
			read_line(var);
			node = node->next;
		}
	}
}

char	*get_next_line(int fd)
{
	static t_var	var[LIMIT];
	char			*str;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > LIMIT
		|| (var[fd].eof && var[fd].fin))
		return (NULL);
	if (!var[fd].run)
	{
		var[fd].offset = 0;
		var[fd].fd = fd;
	}
	var[fd].nlb = 0;
	set_line(&var[fd]);
	if (var[fd].nlb == 0 || var[fd].run->len == (size_t) -1)
	{
		var[fd].fin = 1;
		free(var[fd].run);
		return (NULL);
	}
	str = (char *)malloc(sizeof(char) * (var[fd].nlb + 1));
	if (!str)
		return (NULL);
	str[var[fd].nlb] = '\0';
	coppy_line(&var[fd], str);
	return (str);
}
