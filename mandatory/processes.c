/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbazaz <fbazaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 14:03:25 by fbazaz            #+#    #+#             */
/*   Updated: 2024/02/28 16:06:57 by fbazaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*check_cmd(char **paths, char *cmd)
{
	char	*tmp;
	char	*command;

	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		command = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(command, X_OK) == 0)
			return (command);
		free(command);
		paths++;
	}
	return (NULL);
}

char	*get_command_path(char **paths, char *cmd, int n)
{
	if (!paths)
		return (NULL);
	if (cmd[0] == '/' || cmd[0] == '.')
	{
		if (access(cmd, X_OK) == 0)
			return (cmd);
		else
		{
			if (n == 0)
				ft_putendl_fd("zsh: no such file or directory: ", cmd, 2, 127);
			else
				return (NULL);
		}
	}
	return (check_cmd(paths, cmd));
}

void	child_clean(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (pipex->cmds[i])
	{
		free(pipex->cmds[i]);
		i++;
	}
	free(pipex->cmds);
	free(pipex->cmd);
}

void	first_child(t_pipex pipex, char **av, char **env)
{
	if (pipex.infile == -1 && pipex.index == 0)
		ft_putendl_fd("zsh: no such file or directory: ", av[1], 2, 1);
	else if (pipex.index == 1)
		ft_putendl_fd("zsh: permission denied: ", av[1], 2, 1);
	dup2(pipex.infile, 0);
	close(pipex.infile);
	dup2(pipex.pipe_fd[1], 1);
	close(pipex.pipe_fd[1]);
	close(pipex.pipe_fd[0]);
	pipex.cmds = ft_split(av[2], ' ');
	pipex.cmd = get_command_path(pipex.paths, pipex.cmds[0], 0);
	if (!pipex.cmd)
	{
		ft_putendl_fd("zsh: command not found: ", pipex.cmds[0], 2, -1);
		child_clean(&pipex);
		exit(127);
	}
	if (execve(pipex.cmd, pipex.cmds, env) == -1)
		p_err("Error");
}

void	parent_process(t_pipex pipex, char **av, char **env)
{
	dup2(pipex.pipe_fd[0], 0);
	close(pipex.pipe_fd[0]);
	close(pipex.pipe_fd[1]);
	dup2(pipex.outfile, 1);
	close(pipex.outfile);
	pipex.cmds = ft_split(av[3], ' ');
	pipex.cmd = get_command_path(pipex.paths, pipex.cmds[0], 0);
	if (!pipex.cmd)
	{
		ft_putendl_fd("zsh: command not found: ", pipex.cmds[0], 2, -1);
		child_clean(&pipex);
		exit(127);
	}
	parent_clean(&pipex);
	if (execve(pipex.cmd, pipex.cmds, env) == -1)
		p_err("Error");
}
