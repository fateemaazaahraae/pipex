/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbazaz <fbazaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 10:10:14 by fbazaz            #+#    #+#             */
/*   Updated: 2024/02/17 10:17:00 by fbazaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# define ERR_ARG "Please enter at least 5 arguments.\n"
# define ERR_PIPE "Pipe"
# define ERR_CMD "zsh: command not found: "
# define ERR_EXEC "Execve"

# include "../libft/libft.h"
# include <fcntl.h>    // open unlink
# include <stdio.h>    // perror
# include <stdlib.h>   // malloc free exit
# include <sys/wait.h> // wait waitpid
# include <unistd.h>   // read write access pipe fork execve dup dup2

void	child_process(char *cmd, char **env);
char	*find_paths(char *name, char **env);
void	ft_free_tab(char **tab);
char	*find_cmd_path(char *cmd, char **env);
void	ft_execute(char *cmd, char **env);
void	p_error(char *err);
int		put_error(char *err);

/* size_t	ft_strlen(char *s);
char	*ft_strdup(char *src);
int		count_word(char *s, char c);
char	**free_array(char **array);
char	*ft_strncpy(char *dest, char *src, int len);
int		fill_array(char *s, char **array, char c, int count);
char	**ft_split(char *s, char c);
char	*ft_strjoin(char *s1, char *s2);
int	ft_strncmp(char *s1, char *s2, size_t n); */

#endif