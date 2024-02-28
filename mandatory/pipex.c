/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbazaz <fbazaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 09:24:39 by fbazaz            #+#    #+#             */
/*   Updated: 2024/02/28 16:00:00 by fbazaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	parent_clean(t_pipex *pipex)
{
	int	i;

	close(pipex->infile);
	close(pipex->outfile);
	close(pipex->pipe_fd[0]);
	close(pipex->pipe_fd[1]);
	i = 0;
	while (pipex->paths[i])
	{
		free(pipex->paths[i]);
		i++;
	}
	free(pipex->paths);
}

char	*find_path(char *name, char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], name, 5) == 0)
			return (env[i] + 5);
		i++;
	}
	return (NULL);
}

void	parce_cmd(char **av)
{
	if (!av[2][0] && !av[3][0])
	{
		av[2] = "cat";
		av[3] = "cat";
	}
	else if (!av[2][0])
		av[2] = "cat";
	else if (!av[3][0])
		av[3] = "cat";
}

int	ft_open(char *file, int n)
{
	int	fd;

	if (n == 0)
		fd = open(file, O_RDONLY);
	else
		fd = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	return (fd);
}

int	main(int ac, char **av, char **env)
{
	t_pipex	pipex;

	if (ac != 5)
		ft_putendl_fd("Please enter 5 arguments.", NULL, 2, 1);
	parce_cmd(av);
	pipex.infile = ft_open(av[1], 0);
	pipex.outfile = ft_open(av[ac - 1], 1);
	if (pipe(pipex.pipe_fd) == -1)
		p_err("Error");
	pipex.all_path = find_path("PATH=", env);
	pipex.paths = ft_split(pipex.all_path, ':');
	if (errno == 13)
		pipex.index = 1;
	pipex.pid1 = fork();
	if (pipex.pid1 == 0)
		first_child(pipex, av, env);
	wait(NULL);
	if (pipex.outfile == -1)
		ft_putendl_fd("zsh: no such file or directory: ", av[4], 2, 1);
	parent_process(pipex, av, env);
	if (!get_command_path(pipex.paths, av[3], 1))
		exit(127);
	return (0);
}
