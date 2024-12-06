/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knakto <knakto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 22:55:12 by knakto            #+#    #+#             */
/*   Updated: 2024/12/01 02:20:05 by knakto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <sys/wait.h>
# include <errno.h>
# include "../KML/include/kml.h"

typedef struct s_tool
{
	int		pipe_fd[2];
	int		file_fd[2];
	pid_t	pid1;
	pid_t	pid2;
	char	*path_cmd;
	char	**all_path;
	char	**envp;
	char	**cmd;
}	t_tool;

// void	reerror(char *txt);
// char	**get_path(char **envp);
// char	*can_access(char **path, char **v, t_tool *tool);
// void	ft_execute(char **cmd, t_tool *tool, char **envp);
// void	fileinit(t_tool *tool, char **v);
// void	child1(t_tool *tool, char **envp, char **v);
// void	child2(t_tool *tool, char **envp, char **v);
// void	close_fd(t_tool *tool);

#endif
