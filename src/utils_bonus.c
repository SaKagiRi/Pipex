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

#include "../include/pipex_bonus.h"

char	**getpath(t_exe *tool)
{
	int	i;

	i = 0;
	while (tool->envp[i])
		if (ft_strncmp(tool->envp[i++], "PATH=", 5) == 0)
			return (ft_split(tool->envp[i - 1] + 5, ':'));
	return (ft_split("/core/dump /core/dump/eiei", ' '));
}

int	check_access(t_exe *tool)
{
	int	i;
	int	status;

	i = -1;
	status = check_cmdpath(tool);
	if (status == 1)
		return (1);
	while (tool->all_path[++i] && status == 0)
	{
		tool->all_path[i] = fjoin(tool->all_path[i], "/");
		tool->all_path[i] = fjoin(tool->all_path[i], tool->cmd[0]);
		if (access(tool->all_path[i], X_OK | F_OK) == 0)
		{
			tool->path_cmd = ft_strdup(tool->all_path[i]);
			free_split(tool->all_path);
			return (0);
		}
	}
	if (tool->all_path)
		free_split(tool->all_path);
	perror(tool->cmd[0]);
	if (tool->cmd)
		free_split(tool->cmd);
	return (-1);
}

int	check_cmdpath(t_exe *tool)
{
	int	i;

	i = 0;
	while (tool->cmd[0][i])
	{
		if (tool->cmd[0][i++] == '/')
		{
			if (access(tool->cmd[1], X_OK | F_OK) == 0)
			{
				tool->path_cmd = tool->cmd[0];
				tool->cmd[0] = ft_strdup(ft_strrchr(tool->cmd[0], '/') + 1);
				if (tool->all_path)
					free_split(tool->all_path);
				return (1);
			}
			return (-1);
		}
	}
	if (!tool->all_path)
		return (-1);
	return (0);
}

void	ft_free(t_tool *tool)
{
	free(tool->pid);
	exit(EXIT_FAILURE);
}

void	process_out(t_tool *tool, int i, char *cmd, char **envp)
{
	int count;

	count = 0;
	tool->pid[i] = fork();
	if (tool->pid[i] < 0)
	{
		perror("fork: process_out");
		free(tool->pid);
		close(tool->file_out);
		exit(EXIT_FAILURE);
	}
	if (tool->pid[i] == 0)
	{
		dup2(tool->file_out, 1);
		close(tool->file_out);
		execute(cmd, envp);
	}
	wait(0);
	while (count < i)
		waitpid(tool->pid[count++], 0, 0);
	if (tool->pid)
		free(tool->pid);
}
