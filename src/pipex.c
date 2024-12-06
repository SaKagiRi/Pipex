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
	close(tool->pipe_fd[1]);
	dup2(tool->file_fd[0], 0);
	close(tool->file_fd[0]);
	if (pipe(tool->pipe_fd) < 0)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
}

void	fork_process(t_tool *tool, char **v)
{
	tool->pid1 = fork();
	if (tool->pid1 < 0)
	{
		ft_close_fd(tool);
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (tool->pid1 == 0)
		process_in(tool, v);
	else
	{
		close(tool->pipe_fd[1]);
		dup2(tool->pipe_fd[0], 0);
		close(tool->pipe_fd[0]);
	}
	tool->pid2 = fork();
	if (tool->pid2 < 0)
	{
		ft_close_fd(tool);
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (tool->pid2 == 0)
		process_out(tool, v);
}

int	main(int c, char **v, char **envp)
{
	t_tool	tool;

	if (c != 5)
		return (pnf("./pipex file_in cmd1 cmd2 file_out"));
	ft_init(&tool, v, envp);
	fork_process(&tool, v);
	close(tool.file_fd[1]);
	waitpid(tool.pid1, 0, 0);
	waitpid(tool.pid2, 0, 0);
}
