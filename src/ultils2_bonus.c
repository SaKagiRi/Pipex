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

#include "../include/pipex_bonus.h"

void	here_doc_init(t_tool *tool, int file_fd, int c)
{
	close(file_fd);
	file_fd = open(".here_doc_temp", O_RDONLY);
	dup2(file_fd, 0);
	close(file_fd);
	tool->pid = malloc(sizeof(pid_t) * c);
	if (!tool->pid)
	{
		perror("malloc: here_doc_init");
		exit(EXIT_FAILURE);
	}
	unlink(".here_doc_temp");
}

void	run(int pipe_fd[2], char *cmd, char **envp)
{
	close(pipe_fd[0]);
	dup2(pipe_fd[1], 1);
	close(pipe_fd[1]);
	execute(cmd, envp);
}

void	check_file_in(t_tool *tool)
{
	int	file_fd;

	file_fd = open(tool->file_in, O_RDONLY);
	if (file_fd == -1)
	{
		perror(tool->file_in);
		free(tool->pid);
		exit(EXIT_FAILURE);
	}
}

void	ft_file_out(t_tool *tool)
{
	tool->file_out = open(tool->file_end, O_WRONLY | O_CREAT | O_TRUNC, RW);
	if (tool->file_out < 0)
	{
		perror(tool->file_end);
		free(tool->pid);
		exit(EXIT_FAILURE);
	}
}
