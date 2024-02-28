/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbazaz <fbazaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 09:48:02 by fbazaz            #+#    #+#             */
/*   Updated: 2024/02/28 16:24:28 by fbazaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	p_error(char *err)
{
	perror(err);
	exit(1);
}

void	child_process(t_pipex pipex, char **av, char **env)
{
	pid_t	pid;
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		p_error("Error");
	pid = fork();
	if (pipex.i == 2 && pipex.infile == -1 && pid == 0 && pipex.index == 0)
		ft_putendl_fd("zsh: no such file or directory: ", av[1], 2, 1);
	else if (pipex.i == 2 && pipex.infile == -1 && pid == 0 && pipex.index == 1)
		ft_putendl_fd("zsh: permission denied: ", av[1], 2, 1);
	else if (pipex.i == 2 && pipex.infile != -1 && pid == 0)
		dup2(pipex.infile, 0);
	if (pid == 0)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], 1);
		close(pipe_fd[1]);
		ft_execute(av[pipex.i], env);
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
		fd = open(file, O_RDONLY);
	else if (n == 1)
		fd = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else
		fd = open(file, O_WRONLY | O_APPEND | O_CREAT, 0644);
	return (fd);
}

int	main(int ac, char **av, char **env)
{
	t_pipex	pipex;

	if (ac < 5)
		ft_putendl_fd("Please enter at least 5 argumets.", NULL, 2, 1);
	set_up(ac, av, &pipex);
	if (errno == 13)
		pipex.index = 1;
	while (pipex.i < ac - 2)
	{
		child_process(pipex, av, env);
		pipex.i++;
	}
	waitpid(-1, NULL, 0);
	if (pipex.outfile == -1)
		ft_putendl_fd("zsh: no such file or directory: ", av[ac - 1], 2, 1);
	dup2(pipex.outfile, 1);
	close(pipex.outfile);
	ft_execute(av[ac - 2], env);
	if (!find_cmd_path(av[ac - 2], env, 1))
		exit(127);
}
