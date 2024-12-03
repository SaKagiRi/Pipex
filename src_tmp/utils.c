/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knakto <knakto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by ░░░░██░░          #+#    #+#             */
/*   Updated: 2024/12/01 01:25:28 by knakto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

**                             ▒▒▒▒▒▒▒▒▒▒▒▒                                   **
**                           ▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒                             **
**                         ▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒                           **
**                         ░░░░▒▒▒▒░░▒▒▒▒░░▒▒▒▒░░░░                           **
**                         ░░░░░░▒▒▒▒▒▒▒▒▒▒▒▒░░░░░░                           **
**                         ░░░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░░░                           **
**                             ▒▒▒▒▒▒    ▒▒▒▒▒▒                               **
**                           ▓▓▓▓▓▓        ▓▓▓▓▓▓                             **
**                         ▓▓▓▓▓▓▓▓        ▓▓▓▓▓▓▓▓                           **
**           ████████████████████████████████████████████████████             **
**           ██░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░██             **
**           ██▒▒▒▒▒▒▒▒░░░░░░░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒██             **
**           ██░░░░▒▒▒▒░░░░░░░░▒▒░░░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒░░░░░░▒▒██             **
**           ██░░░░▒▒▒▒░░░░░░░░▒▒░░░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒░░░░▒▒██             **
**           ██░░░░▒▒▒▒░░░░░░░░▒▒░░░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒░░░░░░▒▒██             **
**           ██░░░░▒▒▒▒░░░░░░░░▒▒░░░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒░░░░▒▒██             **
**           ██░░░░▒▒▒▒░░░░░░░░▒▒░░░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒░░░░░░▒▒██             */
/*                                                                            */
/*   By:      Pipeeeeeeeeeeeee X                                              */
/*                                                                            */
/*   Created:   by   knakto                                                   */
/*   Updated:   by   knakto                                                   */
/*                                                                            */
/* ************************************************************************** */

#include "../KML/include/kml.h"
#include "pipex.h"

void	reerror(char *txt, int errornum, int fd)
{
	if (fd < 0)
		close(fd);
	perror(txt);
	exit(errornum);
}

char	**get_path(char **envp)
{
	int		i;
	char	**str;
	char	*n;

	i = 0;
	n = NULL;
	str = (fsplit(argstr("PATH=", envp), '\n'));
	while (str[i])
	{
		if ((ft_strncmp("PATH=", str[i++], 5) == 0))
		{
			n = ft_strdup(str[i - 1]);
			break ;
		}
	}
	str = free_split(str);
	str = fsplit(n, '=');
	n = ft_strdup(str[1]);
	str = free_split(str);
	str = fsplit(n, ':');
	return (str);
}

char	*can_access(char **path, char **v, t_tool *tool)
{
	int		i;
	char	*str;

	i = 0;
	if (access(v[0], X_OK | F_OK) == 0)
	{
		str = v[0];
		v[0] = ft_strrchr(v[0], '/');
		return (str);
	}
	while (path[i])
	{
		path[i] = fjoin(path[i], "/");
		path[i] = fjoin(path[i], v[0]);
		if (access(path[i], X_OK | F_OK) == 0)
			return (ft_strdup(path[i]));
		i++;
	}
	if (tool->cmd1)
		free_split(tool->cmd1);
	if (tool->cmd2)
		free_split(tool->cmd2);
	free_split(path);
	reerror("command not found", 1, 0);
	return (NULL);
}

void	close_fd(t_tool *tool)
{
	close(tool->pipe_fd[0]);
	close(tool->pipe_fd[1]);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knakto <knakto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 23:07:45 by knakto            #+#    #+#             */
/*   Updated: 2024/11/22 02:00:18 by knakto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
