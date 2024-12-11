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

# ifndef RW
#  define RW 0666
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
	int		file_out;
	pid_t	*pid;
}	t_tool;

void	execute(char *cmd, char **envp);
void	file_init(t_tool *tool, char *file_in, int count);
void	process(t_tool *tool, int num_program, char *cmd, char **envp);
void	ft_heredoc(t_tool *tool, char *v, int c);
void	here_doc_init(t_tool *tool, int file_fd, int c);
char	**getpath(t_exe *tool);
void	check_access(t_exe *tool);
int		check_cmdpath(t_exe *tool);
void	ft_free(t_tool *tool);
void	process_out(t_tool *tool, int i, char *cmd, char **envp);

#endif
