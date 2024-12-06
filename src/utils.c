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

int	check_cmdpath(t_tool *tool)
{
	int	i;

	i = 0;
	while (tool->cmd[0][i])
	{
		if (tool->cmd[0][i++] == '/')
		{
			if (access(tool->cmd[0], X_OK | F_OK) == 0)
			{
				tool->path_cmd = tool->cmd[0];
				tool->cmd[0] = ft_strdup(ft_strrchr(tool->cmd[0], '/') + 1);
				if (tool->all_path)
					free_split(tool->all_path);
				return (1);
			}
			if (tool->all_path)
				free_split(tool->all_path);
			perror(tool->cmd[0]);
			free_split(tool->cmd);
			exit(EXIT_FAILURE);
		}
	}
	if (!tool->all_path)
		return (-1);
	return (0);
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

void	execute(t_tool *tool, char **v, int num_cmd)
{
	tool->cmd = ft_split(v[num_cmd], ' ');
	tool->all_path = getpath(tool);
	if (!tool->all_path)
	{
		free(tool->cmd);
		exit(EXIT_FAILURE);
	}
	check_access(tool);
	if (execve(tool->path_cmd, tool->cmd, tool->envp) == -1)
	{
		ft_close_fd(tool);
		if (tool->cmd)
			free_split(tool->cmd);
		free(tool->path_cmd);
	}
	if (tool->cmd)
		free_split(tool->cmd);
	free(tool->path_cmd);
}
