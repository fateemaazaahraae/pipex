/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbazaz <fbazaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 10:28:58 by fbazaz            #+#    #+#             */
/*   Updated: 2024/02/28 10:08:34 by fbazaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*find_paths(char *name, char **env)
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

void	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

char	*check_cmd(char **paths, char *cmd)
{
	char	*tmp;
	char	*command;
	char	**cmd_args;

	cmd_args = ft_split(cmd, ' ');
	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		command = ft_strjoin(tmp, cmd_args[0]);
		free(tmp);
		if (access(command, X_OK) == 0)
			return (command);
		free(command);
		paths++;
	}
	return (NULL);
}

char	*find_cmd_path(char *cmd, char **env, int n)
{
	char	*path;
	char	**all_paths;

	path = find_paths("PATH=", env);
	all_paths = ft_split(path, ':');
	if (!all_paths)
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
	return (check_cmd(all_paths, cmd));
}

void	ft_execute(char *cmd, char **env)
{
	char	*cmd_path;
	char	**cmd_args;

	cmd_args = ft_split(cmd, ' ');
	cmd_path = find_cmd_path(cmd, env, 0);
	if (!cmd_path)
	{
		ft_putendl_fd("zsh: command not found: ", cmd_args[0], 2, 127);
		ft_free_tab(cmd_args);
	}
	if (execve(cmd_path, cmd_args, env) == -1)
		p_error("Error");
}
