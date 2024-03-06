/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbazaz <fbazaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 10:10:14 by fbazaz            #+#    #+#             */
/*   Updated: 2024/03/04 11:16:06 by fbazaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# define BUFFER_SIZE 42

# define ERR_ARG "Please enter at least 5 arguments.\n"

# include "../utils/utils.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct pipex
{
	int	i;
	int	infile;
	int	outfile;
}		t_pipex;

void	p_error(char *err);
int		ft_open(char *file, int n);
void	child_process(t_pipex pipex, char **av, char **env);
void	norminette_25_line(t_pipex pipex, char **av);

char	*find_paths(char *name, char **env);
void	ft_free_tab(char **tab);
char	*check_cmd(char **paths, char *cmd);
char	*find_cmd_path(char *cmd, char **env);
void	ft_execute(char *cmd, char **env);

void	here_doc_run(char **av);
void	here_doc_input(char **av, int *fd);
void	set_up(int ac, char **av, t_pipex *pipex);

char	*ft_read_line(int fd, char *str);
char	*ft_fill(char *str);
char	*ft_new_str(char *str);
char	*get_next_line(int fd);

#endif
