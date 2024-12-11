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
