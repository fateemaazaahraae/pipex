/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbazaz <fbazaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 12:40:19 by fbazaz            #+#    #+#             */
/*   Updated: 2024/02/28 12:48:36 by fbazaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	here_doc_input(int ac, char **av, int *fd)
{
	char	*line;

	close(fd[0]);
	while (1)
	{
		line = get_next_line(0, ac);
		if (ft_strncmp(line, av[2], ft_strlen(av[2])) == 0)
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

void	here_doc_run(char **av, int ac)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		p_error("Error");
	pid = fork();
	if (pid == 0)
		here_doc_input(ac, av, fd);
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
			ft_putendl_fd("Please enter at least 6 argumets.", NULL, 2, 1);
		pipex->i = 3;
		pipex->outfile = ft_open(av[ac - 1], 2);
		here_doc_run(av, ac);
	}
	else
	{
		pipex->i = 2;
		pipex->infile = ft_open(av[1], 0);
		pipex->outfile = ft_open(av[ac - 1], 1);
	}
}
