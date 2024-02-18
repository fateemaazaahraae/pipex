/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbazaz <fbazaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 09:24:39 by fbazaz            #+#    #+#             */
/*   Updated: 2024/02/18 09:38:26 by fbazaz           ###   ########.fr       */
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
	{
		fd = open(file, O_RDONLY);
		if (fd == -1)
			p_err("Error");
	}
	else
	{
		fd = open(file, O_RDWR | O_TRUNC | O_CREAT, 0777);
		if (fd == -1)
			p_err("Error");
	}
	return (fd);
}

int	main(int ac, char **av, char **env)
{
	t_pipex	pipex;

	if (ac != 5)
		return (put_err(ERR_INPUT));
	parce_cmd(av);
	pipex.infile = ft_open(av[1], 0);
	pipex.outfile = ft_open(av[ac - 1], 1);
	if (pipe(pipex.pipe_fd) == -1)
		p_err(ERR_PIPE);
	pipex.all_path = find_path("PATH=", env);
	pipex.paths = ft_split(pipex.all_path, ':');
	pipex.pid1 = fork();
	if (pipex.pid1 == 0)
		first_child(pipex, av, env);
	pipex.pid2 = fork();
	if (pipex.pid2 == 0)
		second_child(pipex, av, env);
	// waitpid(-1, NULL, 0);
	wait(NULL);
	wait(NULL);
	parent_clean(&pipex);
	if (!get_command_path(pipex.paths, av[3]))
		exit(127);
	return (0);
}
