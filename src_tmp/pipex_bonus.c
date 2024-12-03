/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knakto <knakto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 20:53:06 by knakto            #+#    #+#             */
/*   Updated: 2024/11/30 20:58:36 by knakto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

void	exe(t_tool *tool)
	{
	char	**gpath;
	char	*path;

	gpath = get_path(tool->envp);
	if (!gpath)
		reerror("PATH", tool);
	path = can_access(gpath, tool);
	free_split(gpath);
	if ((execve(path, tool->cmd, tool->envp)))
	{
		free_split(tool->cmd);
		free(tool->pid);
		free(path);
		reerror("text", tool);
	}
}

void	process(t_tool *tool)
{
	int	pipe_fd[2];

	if (pipe(pipe_fd) < 0)
		reerror("text", tool);
	tool->pid[tool->i] = fork();
	if (tool->pid[tool->i] < 0)
		reerror("text", tool);
	if (tool->pid[tool->i] == 0)
	{
		tool->cmd = ft_split(tool->v[tool->i], ' ');
		close(pipe_fd[0]);
		dup2(pipe_fd[1], 1);
		close(pipe_fd[1]);
		exe(tool);
		free_split(tool->cmd);
	}
	else
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], 0);
		close(pipe_fd[0]);
	}
	tool->i++;
}

void	file_init(t_tool *tool)
{
	int	file_fd;

	file_fd = open(tool->v[1], O_RDONLY);
	if (file_fd == -1)
		reerror(tool->v[1], NULL);
	dup2(file_fd, 0);
	close(file_fd);
	tool->pid = malloc(sizeof(pid_t));
	if (!tool->pid)
		reerror("text", tool);
	tool->i = 2;
	tool->wp = 2;
}

void	ft_heredoc(t_tool *tool)
{
	int		file_fd;
	int		len;
	char	*str;

	len = ft_strlen(tool->v[2]);
	file_fd = open(".here_doc_temp", O_WRONLY | O_CREAT | O_TRUNC, IRWXG);
	write(0, "here_doc>", 10);
	str = get_next_line(0);
	while (str != NULL)
	{
		if (ft_strncmp(str, tool->v[2], len) == 0 && ft_strlen(str) - 1 == (size_t) len)
		{
			here_doc_init(tool, file_fd);
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
	t_tool	tool;

	if (c < 5 || (c < 6 && ft_strncmp(v[1], "here_doc", 9) == 0))
		return (pnf("failed input"));
	tool.out_fd = open(v[c - 1], O_WRONLY | O_CREAT | O_TRUNC, IRWXG);
	tool.c = c;
	tool.v = v;
	tool.all_cmd = &v[2];
	tool.envp = envp;
	if (ft_strncmp(v[1], "here_doc", 9) == 0)
		ft_heredoc(&tool);
	else
		file_init(&tool);
	while (tool.i < c - 2)
		process(&tool);
	if (tool.pid[c - 3] != 0)
		last_cmd(&tool);
	while (tool.wp < c - 1)
		waitpid(tool.pid[tool.wp++], 0, 0);
	free(tool.pid);
}
