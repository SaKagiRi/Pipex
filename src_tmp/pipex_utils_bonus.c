/*
*/
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

void	last_cmd(t_tool *tool)
{
	dup2(tool->out_fd, 1);
	close(tool->out_fd);
	tool->cmd = ft_split(tool->v[tool->c - 2], ' ');
	exe(tool);
	free_split(tool->cmd);
}

char	*can_access(char **path, t_tool *tool)
{
	int		i;
	char	*str;

	i = 0;
	if (access(tool->cmd[0], X_OK | F_OK) == 0)
	{
		str = tool->cmd[0];
		tool->cmd[0] = ft_strrchr(tool->cmd[0], '/');
		return (str);
	}
	while (path[i])
	{
		path[i] = fjoin(path[i], "/");
		path[i] = fjoin(path[i], tool->cmd[0]);
		if (access(path[i], X_OK | F_OK) == 0)
			return (ft_strdup(path[i]));
		i++;
	}
	free(tool->pid);
	free_split(path);
	reerror(*tool->cmd, tool);
	return (NULL);
}

char	**get_path(char **envp)
{
	int		i;
	char	**str;
	char	*n;
	char	*temp;

	i = 0;
	n = NULL;
	temp = (argstr("PATH=", envp));
	if(*temp == '\0')
	{
		free(temp);
		return (NULL);
	}
	str = (fsplit(temp, '\n'));
	while (str[i])
	{
		if ((ft_strncmp("PATH=", str[i++], 5) == 0))
		{
			n = ft_strdup(str[i - 1]);
			str = ft_split(n + 5, ':');
			free(n);
			return (str);
		}
	}
	free(temp);
	free(str);
	return (NULL);
}

void	reerror(char *text, t_tool *tool)
{
	perror(text);
	if (tool->cmd && tool != NULL)
		free_split(tool->cmd);
	exit(EXIT_FAILURE);
}

void	here_doc_init(t_tool *tool, int file_fd)
{
	close(file_fd);
	file_fd = open(".here_doc_temp", O_RDONLY);
	dup2(file_fd, 0);
	close(file_fd);
	tool->pid = malloc(sizeof(pid_t) * tool->c);
	if (!tool->pid)
		reerror("text", tool);
	tool->i = 3;
	tool->wp = 3;
	unlink(".here_doc_temp");
}
