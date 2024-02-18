/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbazaz <fbazaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 14:03:25 by fbazaz            #+#    #+#             */
/*   Updated: 2024/02/17 11:09:13 by fbazaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_command_path(char **paths, char *cmd)
{
	char	*tmp;
	char	*command;

	if (!paths)
		return (NULL);
	if (cmd[0] == '.')
	{
		if (access(cmd, X_OK) == 0)
			return (cmd);
	}
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
	dup2(pipex.infile, 0);
	close(pipex.infile);
	dup2(pipex.pipe_fd[1], 1);
	close(pipex.pipe_fd[1]);
	close(pipex.pipe_fd[0]);
	pipex.cmds = ft_split(av[2], ' ');
	pipex.cmd = get_command_path(pipex.paths, pipex.cmds[0]);
	if (!pipex.cmd)
	{
		child_clean(&pipex);
		put_err(ERR_CMD);
		write(2, av[2], ft_strlen(av[2]));
		write(2, "\n", 1);
		exit(1);
	}
	if (execve(pipex.cmd, pipex.cmds, env) == -1)
		p_err(ERR_EXEC);
}

void	second_child(t_pipex pipex, char **av, char **env)
{
	dup2(pipex.pipe_fd[0], 0);
	close(pipex.pipe_fd[0]);
	close(pipex.pipe_fd[1]);
	dup2(pipex.outfile, 1);
	close(pipex.outfile);
	pipex.cmds = ft_split(av[3], ' ');
	pipex.cmd = get_command_path(pipex.paths, pipex.cmds[0]);
	if (!pipex.cmd)
	{
		child_clean(&pipex);
		put_err(ERR_CMD);
		write(2, av[3], ft_strlen(av[3]));
		write(2, "\n", 1);
		exit(1);
	}
	if (execve(pipex.cmd, pipex.cmds, env) == -1)
		p_err(ERR_EXEC);
}
