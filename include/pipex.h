/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knakto <knakto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 22:55:12 by knakto            #+#    #+#             */
/*   Updated: 2024/11/28 16:44:40 by knakto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <sys/wait.h>

typedef struct s_tool
{
	int		pipe_fd[2];
	int		file_fd[2];
	pid_t	pid1;
	pid_t	pid2;
	char	**cmd1;
	char	**cmd2;
}	t_tool;

void	reerror(char *txt, int num, int fd);
char	**get_path(char **envp);
char	*can_access(char **path, char **v, t_tool *tool);
void	ft_execute(char **cmd, t_tool *tool, char **envp);
void	fileinit(t_tool *tool, char **v);
void	child1(t_tool *tool, char **envp, char **v);
void	child2(t_tool *tool, char **envp, char **v);
void	close_fd(t_tool *tool);

#endif
