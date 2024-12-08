/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knakto <knakto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 22:55:12 by knakto            #+#    #+#             */
/*   Updated: 2024/12/06 23:10:03 by knakto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <stdio.h>
# include <sys/wait.h>
# include <errno.h>
# include "../KML/include/kml.h"

# ifndef rwx
# define rwx 0666
# endif

typedef struct s_exe
{
	char	*path_cmd;
	char	**all_path;
	char	**envp;
	char	**cmd;
}	t_exe;

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

int		check_cmdpath(t_exe *tool);
void	check_access(t_exe *tool);
void	execute(char *cmd, char **envp);
void	ft_init(t_tool *tool, char **v, char **envp);
void	fork_process(t_tool *tool, char **v);
void	process_in(t_tool *tool, char **v);
void	ft_close_fd(t_tool *tool);
void	process_out(t_tool *tool, char **v);
char	**getpath(t_exe *tool);

#endif
