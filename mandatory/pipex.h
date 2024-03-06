/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbazaz <fbazaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 09:24:42 by fbazaz            #+#    #+#             */
/*   Updated: 2024/03/04 11:35:26 by fbazaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../utils/utils.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct pipex
{
	int		pipe_fd[2];
	int		infile;
	int		outfile;
	pid_t	pid1;
	char	*all_path;
	char	**paths;
	char	**cmds;
	char	*cmd;

}			t_pipex;

char		*find_path(char *name, char **env);
void		parent_clean(t_pipex *pipex);
void		first_child(t_pipex pipex, char **av, char **env);
void		parent_process(t_pipex pipex, char **av, char **env);
char		*get_command_path(char **paths, char *cmd);
void		clean_up(t_pipex *pipex);
// void	parce_cmd(char **av);
int			ft_open(char *file, int n);
char		*check_cmd(char **paths, char *cmd);
void		p_err(char *err);

#endif