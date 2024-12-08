/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knakto <knakto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 21:00:51 by knakto            #+#    #+#             */
/*   Updated: 2024/12/06 23:51:20 by knakto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

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

void	execute(char *cmd, char **envp)
{
	t_exe	tool;

	tool.envp = envp;
	tool.cmd = ft_split(cmd, ' ');
	tool.all_path = getpath(&tool);
	check_access(&tool);
	execve(tool.path_cmd, tool.cmd, envp);
	free_split(tool.cmd);
	free(tool.path_cmd);
	exit(EXIT_FAILURE);
}

int	main(int c, char **v, char **envp)
{
	(void)c;
	(void)v;
	pid_t pid;

	pid = fork();
	if (pid == 0)
	{
		execute(v[1], envp); // สามารพใช้ ฟังค์ชั่นแล้วทำงานได้เลย
	}
	wait(0);
}
