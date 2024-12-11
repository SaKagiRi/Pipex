/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*                                                                            **
**                                                                            **
**                               ▒▒▒▒▒▒▒▒▒▒                                   **
**                             ▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒                             **
**                             ▓▓▓▓▓▓░░░░██░░                                 **
**                           ▓▓░░▓▓░░░░░░██░░░░                               **
**                           ▓▓░░▓▓▓▓░░░░░░██░░░░░░                           **
**                           ▓▓▓▓░░░░░░░░████████                             **
**                               ░░░░░░░░░░░░░░                               **
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
}

void	file_init(t_tool *tool, char *file_in, int count)
{
	int	file_fd;

	file_fd = open(file_in, O_RDONLY);
	if (file_fd == -1)
	{
		perror(file_in);
		exit(EXIT_FAILURE);
	}
	dup2(file_fd, 0);
	close(file_fd);
	tool->pid = malloc(sizeof(pid_t) * count);
	if (!tool->pid)
	{
		perror("fork: file_init");
		exit(EXIT_FAILURE);
	}
}

void	process(t_tool *tool, int num_program, char *cmd, char **envp)
{
	int	pipe_fd[2];

	if (pipe(pipe_fd) < 0)
	{
		perror("pipe: process");
		free(tool->pid);
		exit(EXIT_FAILURE);
	}
	tool->pid[num_program] = fork();
	if (tool->pid[num_program] < 0)
	{
		perror("fork: process");
		free(tool->pid);
		exit(EXIT_FAILURE);
	}
	if (tool->pid[num_program] == 0)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], 1);
		close(pipe_fd[1]);
		execute(cmd, envp);
	}
	close(pipe_fd[1]);
	dup2(pipe_fd[0], 0);
	close(pipe_fd[0]);
}

void	ft_heredoc(t_tool *tool, char *v, int c)
{
	int		file_fd;
	int		len;
	char	*str;

	len = ft_strlen(v);
	file_fd = open(".here_doc_temp", O_WRONLY | O_CREAT | O_TRUNC, RW);
	write(0, "here_doc>", 10);
	str = get_next_line(0);
	while (str != NULL)
	{
		if (ft_strncmp(str, v, len) == 0 && ft_strlen(str) - 1 == (size_t) len)
		{
			here_doc_init(tool, file_fd, c);
			free(str);
			return ;
		}
		write(file_fd, str, ft_strlen(str));
		free(str);
		write(0, "here_doc>", 9);
		str = get_next_line(0);
	}
	unlink(".here_doc_temp");
	free(str);
	exit(1);
}

int	main(int c, char **v, char **envp)
{
	t_tool	files;
	int		i;
	int		mode;

	if (c < 5 || (c < 6 && ft_strncmp(v[1], "here_doc", 9) == 0))
		return (pnf("	./pipex file_in cmd1 cmd2 ... file_out\n \
	./pipex here_doc eof cmd1 cmd2 ... file_out"));
	files.file_out = open(v[c - 1], O_WRONLY | O_CREAT | O_TRUNC, RW);
	if (ft_strncmp(v[1], "here_doc", 9) == 0)
	{
		ft_heredoc(&files, v[2], c);
		mode = 3;
	}
	else
	{
		file_init(&files, v[1], c);
		mode = 2;
	}
	i = -1;
	while (++i != c - (mode + 2))
		process(&files, i, v[i + mode], envp);
	process_out(&files, i, v[i + mode], envp);
}
