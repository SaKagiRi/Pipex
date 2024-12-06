/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knakto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 21:48:58 by knakto            #+#    #+#             */
/*   Updated: 2024/12/06 21:49:18 by knakto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	process_in(t_tool *tool, char **v)
{
	close(tool->file_fd[1]);
	close(tool->pipe_fd[0]);
	dup2(tool->pipe_fd[1], 1);
	close(tool->pipe_fd[1]);
	execute(tool, &v[2], 0);
}

void	process_out(t_tool *tool, char **v)
{
	dup2(tool->file_fd[1], 1);
	close(tool->file_fd[1]);
	close(tool->pipe_fd[1]);
	dup2(tool->pipe_fd[0], 0);
	close(tool->pipe_fd[0]);
	execute(tool, &v[2], 1);
}

char	**getpath(t_tool *tool)
{
	int	i;

	i = 0;
	while (tool->envp[i])
		if (ft_strncmp(tool->envp[i++], "PATH=", 5) == 0)
			return (ft_split(tool->envp[i - 1] + 5, ':'));
	return (NULL);
}

void	ft_close_fd(t_tool *tool)
{
	close(tool->file_fd[0]);
	close(tool->file_fd[1]);
	close(tool->pipe_fd[0]);
	close(tool->pipe_fd[1]);
}

void	check_access(t_tool *tool)
{
	int	i;
	int	status;

	i = -1;
	status = check_cmdpath(tool);
	if (status == 1)
		return ;
	while (tool->all_path[++i] && status == 0)
	{
		tool->all_path[i] = fjoin(tool->all_path[i], "/");
		tool->all_path[i] = fjoin(tool->all_path[i], tool->cmd[0]);
		if (access(tool->all_path[i], X_OK | F_OK) == 0)
		{
			tool->path_cmd = ft_strdup(tool->all_path[i]);
			free_split(tool->all_path);
			return ;
		}
	}
	if (tool->all_path)
		free_split(tool->all_path);
	perror(tool->cmd[0]);
	if (tool->cmd)
		free_split(tool->cmd);
	exit(EXIT_FAILURE);
}
