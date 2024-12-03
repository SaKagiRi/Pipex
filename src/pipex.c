/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knakto <knakto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 21:00:51 by knakto            #+#    #+#             */
/*   Updated: 2024/12/01 03:39:28 by knakto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	reerror(char *text)
{
	perror(text);	
	exit(EXIT_FAILURE);
}

//have split on return
//return path
char	**getpath(t_tool *tool)
{
	int	i;

	i = 0;
	while (tool->envp[i])
		if (ft_strncmp(tool->envp[i++], "PATH=", 5) == 0)
			return (ft_split(tool->envp[i - 1] + 5, ':'));
	return (NULL);
}

//malloc path
//malloc cmd

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

int	main(int c, char **v, char **envp)
{
	t_tool	tool;
	// char	**str;
	// int	i;

	(void)c;
	(void)envp;

	// //get envp path
	tool.envp = envp;
	tool.cmd = ft_split(v[1], ' ');
	tool.all_path = getpath(&tool);
	if (!tool.all_path)
	{
			free(tool.cmd);
			exit(EXIT_FAILURE);
	}

	check_access(&tool);
	pnf("%s\n", tool.path_cmd);
	pnf("%s\n", tool.cmd[0]);
	execve(tool.path_cmd, tool.cmd, envp);
	if (tool.cmd)
		free_split(tool.cmd);
	free(tool.path_cmd); //finish execut ls /bin/ls and protect /lss lss
}