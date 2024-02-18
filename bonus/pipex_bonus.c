/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbazaz <fbazaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 09:48:02 by fbazaz            #+#    #+#             */
/*   Updated: 2024/02/18 10:06:10 by fbazaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	child_process(char *cmd, char **env)
{
	pid_t	pid;
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		p_error(ERR_PIPE);
	pid = fork();
	if (pid == -1)
		exit(0);
	else if (pid == 0)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], 1);
		close(pipe_fd[1]);
		ft_execute(cmd, env);
	}
	else
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], 0);
		close(pipe_fd[0]);
	}
}

int	ft_open(char *file, int n)
{
	int	fd;

	if (n == 0)
	{
		fd = open(file, O_RDONLY);
		if (fd == -1)
			p_err("Error");
	}
	else if (n == 1)
	{
		fd = open(file, O_RDWR | O_TRUNC | O_CREAT, 0777);
		if (fd == -1)
			p_err("Error");
	}
	else
	{
		fd = open(file, O_RDWR | O_APPEND | O_CREAT, 0777);
		if (fd == -1)
			p_err("Error");
	}
	return (fd);
}

int	main(int ac, char **av, char **env)
{
	int	i;
	int	infile;
	int	outfile;

	if (ac < 5)
		return (put_error(ERR_ARG));
	if (ft_strncmp(av[1], "here_doc", 8) == 0)
	{
		if (ac < 6)
			return (put_error("Enter 6 arguments"));
		i = 3;
		outfile = ft_open(av[ac - 1], 2);
		here_doc_run(av);
	}
	else
	{
		i = 2;
		infile = ft_open(av[1], 0);
		outfile = ft_open(av[ac - 1], 1);
		dup2(infile, 0);
	}
	while (i < ac - 2)
		child_process(av[i++], env);
	wait(NULL);
	if (!find_cmd_path(av[ac - 2], env))
		exit(127);
	dup2(outfile, 1);
	ft_execute(av[ac - 2], env);
}
