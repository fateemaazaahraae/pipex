/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbazaz <fbazaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 12:40:19 by fbazaz            #+#    #+#             */
/*   Updated: 2024/03/04 09:55:10 by fbazaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	here_doc_input(char **av, int *fd)
{
	char	*line;
	char	*delimiter;

	delimiter = ft_strjoin(av[2], "\n");
	close(fd[0]);
	while (1)
	{
		line = get_next_line(0);
		if (ft_strcmp(delimiter, line) == 0)
		{
			free(line);
			close(fd[1]);
			exit(0);
		}
		write(fd[1], line, ft_strlen(line));
		free(line);
	}
	close(fd[1]);
}

void	here_doc_run(char **av)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		p_error("Error");
	pid = fork();
	if (pid == 0)
		here_doc_input(av, fd);
	else
	{
		close(fd[1]);
		dup2(fd[0], 0);
		close(fd[0]);
		wait(NULL);
	}
}

void	set_up(int ac, char **av, t_pipex *pipex)
{
	if (ft_strcmp(av[1], "here_doc") == 0)
	{
		if (ac < 6)
		{
			write(1, "Please enter at least 6 argumets.\n", 35);
			exit(1);
		}
		pipex->i = 3;
		pipex->outfile = ft_open(av[ac - 1], 2);
		here_doc_run(av);
	}
	else
	{
		pipex->i = 2;
		pipex->infile = ft_open(av[1], 0);
		pipex->outfile = ft_open(av[ac - 1], 1);
	}
}
