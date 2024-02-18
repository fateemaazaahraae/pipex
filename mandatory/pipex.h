/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbazaz <fbazaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 09:24:42 by fbazaz            #+#    #+#             */
/*   Updated: 2024/02/17 10:17:15 by fbazaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# define ERR_INPUT "Please enter 5 arguments.\nEx: infile cmd1 cm2 outfile\n"
# define ERR_ENV "Error env !"
# define ERR_PIPE "Pipe"
# define ERR_CMD "zsh: command not found: "
# define ERR_EXEC "Execve"

# include "../libft/libft.h"
# include <fcntl.h>    // open unlink
# include <stdio.h>    // perror
# include <stdlib.h>   // malloc free exit
# include <sys/wait.h> // wait waitpid
# include <unistd.h>   // read write access pipe fork execve dup dup2

typedef struct pipex
{
	int		pipe_fd[2];
	int		infile;
	int		outfile;
	pid_t	pid1;
	pid_t	pid2;
	char	*all_path;
	char	**paths;
	char	**cmds;
	char	*cmd;

}			t_pipex;

// pipex
char		*find_path(char *name, char **env);
void		parent_clean(t_pipex *pipex);
void		first_child(t_pipex pipex, char **av, char **env);
void		second_child(t_pipex pipex, char **av, char **env);
char		*get_command_path(char **paths, char *cmd);
void		child_clean(t_pipex *pipex);

// error
int			put_err(char *err);
void		p_err(char *err);
void		err_file(char *s);

#endif