/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knakto <knakto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 22:55:12 by knakto            #+#    #+#             */
/*   Updated: 2024/11/23 01:52:10 by knakto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../KML/include/kml.h"
# include <fcntl.h>
# include <sys/wait.h>
# include <stdio.h>
# include <unistd.h>

typedef struct s_tool
{
	char	**all_cmd;
	char	**v;
	char	**cmd;
	pid_t	*pid;
	int		wp;
	int		i;
	int		pipe_fd[2];
	int		c;
	int		status;
	char	**envp;
}	t_tool;

void	reerror(char *txt, int errornum, int fd);
char	**get_path(char **envp);
char	*can_access(char **path, t_tool *tool);
void	exe(t_tool *tool);
void	process(t_tool *tool);
void	file_init(t_tool *tool);
void	last_cmd(t_tool *tool);
void	ft_heredoc(t_tool *tool);

#endif
