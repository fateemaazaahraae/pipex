/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbazaz <fbazaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 10:28:58 by fbazaz            #+#    #+#             */
/*   Updated: 2024/03/04 11:42:22 by fbazaz           ###   ########.fr       */
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
	if (!cmd_args[0])
		return (NULL);
	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		command = ft_strjoin(tmp, cmd_args[0]);
		free(tmp);
		if (access(command, X_OK) == 0)
		{
			ft_free_tab(cmd_args);
			return (command);
		}
		free(command);
		paths++;
	}
	ft_free_tab(cmd_args);
	return (NULL);
}

char	*find_cmd_path(char *cmd, char **env)
{
	char	*path;
	char	**all_paths;
	char	*result;

	path = find_paths("PATH=", env);
	all_paths = ft_split(path, ':');
	if (!all_paths)
		return (NULL);
	if (cmd[0] == '/' || cmd[0] == '.')
	{
		if (access(cmd, X_OK) == 0)
			return (cmd);
		else
			ft_putendl_fd(": No such file or directory", cmd, 2, 127);
	}
	result = check_cmd(all_paths, cmd);
	ft_free_tab(all_paths);
	return (result);
}

void	ft_execute(char *cmd, char **env)
{
	char	*cmd_path;
	char	**cmd_args;

	cmd_args = ft_split(cmd, ' ');
	cmd_path = find_cmd_path(cmd, env);
	if (!cmd_path)
	{
		ft_putendl_fd(": command not found", cmd_args[0], 2, -1);
		ft_free_tab(cmd_args);
		exit(127);
	}
	if (execve(cmd_path, cmd_args, env) == -1)
		p_error("Error");
}
