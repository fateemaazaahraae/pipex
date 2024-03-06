/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbazaz <fbazaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 09:48:02 by fbazaz            #+#    #+#             */
/*   Updated: 2024/03/04 11:42:26 by fbazaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	p_error(char *err)
{
	perror(err);
	exit(1);
}

void	norminette_25_line(t_pipex pipex, char **av)
{
	if (pipex.i == 2 && access(av[1], F_OK) == 0 && access(av[1], R_OK) != 0)
		ft_putendl_fd(": Permission denied", av[1], 2, 1);
	else if (pipex.i == 2 && pipex.infile == -1)
		ft_putendl_fd(": No such file or directory", av[1], 2, 1);
	else if (pipex.i == 2 && pipex.infile != -1)
		dup2(pipex.infile, 0);
}

void	child_process(t_pipex pipex, char **av, char **env)
{
	pid_t	pid;
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		p_error("Error");
	pid = fork();
	if (pid == 0)
	{
		norminette_25_line(pipex, av);
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
	{
		write(1, "Please enter at least 5 argumets.\n", 35);
		return (1);
	}
	set_up(ac, av, &pipex);
	while (pipex.i < ac - 2)
	{
		child_process(pipex, av, env);
		pipex.i++;
	}
	wait(NULL);
	if (pipex.outfile == -1)
		ft_putendl_fd(": No such file or directory", av[ac - 1], 2, 1);
	dup2(pipex.outfile, 1);
	close(pipex.outfile);
	ft_execute(av[ac - 2], env);
}
