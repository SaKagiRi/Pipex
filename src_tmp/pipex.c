/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knakto <knakto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 20:55:36 by knakto            #+#    #+#             */
/*   Updated: 2024/11/30 20:55:38 by knakto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../KML/include/kml.h"
#include "../include/pipex.h"

void	ft_execute(char **cmd, t_tool *tool, char **envp)
{
	char	**gpath;
	char	*path;

	gpath = get_path(envp);
	path = can_access(gpath, cmd, tool);
	free_split(gpath);
	if (execve(path, cmd, envp) == -1)
	{
		free_split(cmd);
		free(path);
		reerror("execute failed", 1, 0);
	}
}

void	fileinit(t_tool *tool, char **v)
{
	tool->file_fd[0] = open(v[1], O_RDONLY);
	if (tool->file_fd[0] == -1)
		reerror("open file error", 1, tool->file_fd[0]);
	tool->file_fd[1] = open(v[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (tool->file_fd[1] == -1)
		reerror("can't create file output", 1, tool->file_fd[1]);
}

void	child1(t_tool *tool, char **envp, char **v)
{
	tool->cmd1 = ft_split(v[2], ' ');
	close(tool->pipe_fd[0]);
	dup2(tool->pipe_fd[1], STDOUT_FILENO);
	dup2(tool->file_fd[0], STDIN_FILENO);
	ft_execute(tool->cmd1, tool, envp);
	close(tool->pipe_fd[1]);
	close(tool->file_fd[0]);
	free_split(tool->cmd1);
}

void	child2(t_tool *tool, char **envp, char **v)
{
	tool->cmd2 = ft_split(v[3], ' ');
	close(tool->pipe_fd[1]);
	dup2(tool->pipe_fd[0], STDIN_FILENO);
	dup2(tool->file_fd[1], STDOUT_FILENO);
	ft_execute(tool->cmd2, tool, envp);
	close(tool->pipe_fd[0]);
	close(tool->file_fd[1]);
	free_split(tool->cmd2);
}

/*
--start
--pipe
--fork1 & exec1
--fork2 & close parent fd & exec2
--wait all process
*/
int	main(int c, char **v, char **envp)
{
	t_tool	tool;
	int		status;

	if (c != 5)
		reerror("arg failed", 1, 0);
	if (pipe(tool.pipe_fd) < 0)
		reerror("pipe failed", 1, 0);
	fileinit(&tool, v);
	tool.pid1 = fork();
	if (tool.pid1 < 0)
		reerror("fork failed", 1, 0);
	if (tool.pid1 == 0)
		child1(&tool, envp, v);
	tool.pid2 = fork();
	if (tool.pid2 < 0)
		reerror("fork failed", 1, 0);
	if (tool.pid2 != 0)
		close_fd(&tool);
	if (tool.pid2 == 0)
		child2(&tool, envp, v);
	waitpid(tool.pid1, &status, 0);
	waitpid(tool.pid2, &status, 0);
}
