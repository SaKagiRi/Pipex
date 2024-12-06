/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knakto <knakto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 21:00:51 by knakto            #+#    #+#             */
/*   Updated: 2024/12/05 23:11:53 by knakto           ###   ########.fr       */
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

void	execute(t_tool *tool ,char **v, int num_cmd)
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
		free(tool->path_cmd); //finish execut ls /bin/ls and protect /lss lss
	}
	if (tool->cmd)
		free_split(tool->cmd);
	free(tool->path_cmd); //finish execut ls /bin/ls and protect /lss lss
}

void	ft_init(t_tool *tool, char **v, char **envp)
{
	tool->envp = envp;
	tool->file_fd[1] = open(v[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	tool->file_fd[0] = open(v[1], O_RDONLY);
	if (tool->file_fd[0] < 0)
	{
		perror(v[1]);
		exit(EXIT_FAILURE);
	}
	dup2(tool->file_fd[0], 0);
	close(tool->file_fd[0]);
	if (pipe(tool->pipe_fd) < 0)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
}

int	main(int c, char **v, char **envp)
{
	t_tool	tool;

	if (c != 5)
		return (0);
	ft_init(&tool, v, envp);
	tool.pid1 = fork();
	if (tool.pid1 < 0)
	{
		ft_close_fd(&tool);
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (tool.pid1 == 0)
	{
		close(tool.file_fd[1]);
		close(tool.pipe_fd[0]);
		dup2(tool.pipe_fd[1], 1);
		close(tool.pipe_fd[1]);
		execute(&tool, &v[2], 0);
	}
	else
	{
		close(tool.pipe_fd[1]);
		dup2(tool.pipe_fd[0], 0);
		close(tool.pipe_fd[0]);
	}
	tool.pid2 = fork();
	if (tool.pid2 < 0)
	{
		ft_close_fd(&tool);
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (tool.pid2 == 0)
	{
		dup2(tool.file_fd[1], 1);
		close(tool.file_fd[1]);
		close(tool.pipe_fd[1]);
		dup2(tool.pipe_fd[0], 0);
		close(tool.pipe_fd[0]);
		execute(&tool, &v[2], 1);
	}
	close(tool.file_fd[1]);
	waitpid(tool.pid1, &errno, 0);
	waitpid(tool.pid2, &errno, 0);
}
