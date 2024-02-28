/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbazaz <fbazaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 09:24:42 by fbazaz            #+#    #+#             */
/*   Updated: 2024/02/28 15:58:09 by fbazaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <fcntl.h>    // open unlink
# include <stdio.h>    // perror
# include <stdlib.h>   // malloc free exit
# include <sys/wait.h> // wait waitpid
# include <unistd.h>   // read write access pipe fork execve dup dup2
# include <errno.h>

typedef struct pipex
{
	int		pipe_fd[2];
	int		infile;
	int		outfile;
	pid_t	pid1;
	int		index;
	char	*all_path;
	char	**paths;
	char	**cmds;
	char	*cmd;

}			t_pipex;

// pipex
char	*find_path(char *name, char **env);
void	parent_clean(t_pipex *pipex);
void	first_child(t_pipex pipex, char **av, char **env);
void	parent_process(t_pipex pipex, char **av, char **env);
char	*get_command_path(char **paths, char *cmd, int n);
void	child_clean(t_pipex *pipex);
void	parce_cmd(char **av);
int		ft_open(char *file, int n);
char	*check_cmd(char **paths, char *cmd);

// error
void	p_err(char *err);

#endif