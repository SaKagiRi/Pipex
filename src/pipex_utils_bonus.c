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
	int	file_fd;

	file_fd = open(tool->v[tool->c - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	dup2(file_fd, 1);
	close(file_fd);
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
	if (tool->cmd)
		free_split(tool->cmd);
	free(tool->pid);
	free_split(path);
	reerror("command not found", 0, 0);
	return (NULL);
}

char	**get_path(char **envp)
{
	int		i;
	char	**str;
	char	*n;

	i = 0;
	n = NULL;
	str = (fsplit(argstr("PATH=", envp), '\n'));
	while (str[i])
	{
		if ((ft_strncmp("PATH=", str[i++], 5) == 0))
		{
			n = ft_strdup(str[i - 1]);
			break ;
		}
	}
	str = free_split(str);
	str = fsplit(n, '=');
	n = ft_strdup(str[1]);
	str = free_split(str);
	str = fsplit(n, ':');
	return (str);
}

void	reerror(char *txt, int errornum, int fd)
{
	if (fd < 0)
		close(fd);
	perror(txt);
	exit(errornum);
}
