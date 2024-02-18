/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbazaz <fbazaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 10:28:58 by fbazaz            #+#    #+#             */
/*   Updated: 2024/02/17 10:02:07 by fbazaz           ###   ########.fr       */
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

char	*find_cmd_path(char *cmd, char **env)
{
	char	*path;
	char	**all_paths;
	char	*cmd_path;
	char	**cmd_args;
	char	*tmp;

	path = find_paths("PATH=", env);
	all_paths = ft_split(path, ':');
	cmd_args = ft_split(cmd, ' ');
	while (*all_paths)
	{
		tmp = ft_strjoin(*all_paths, "/");
		cmd_path = ft_strjoin(tmp, cmd_args[0]);
		free(tmp);
		if (access(cmd_path, F_OK) == 0)
		{
			ft_free_tab(cmd_args);
			return (cmd_path);
		}
		free(cmd_path);
		all_paths++;
	}
	return (NULL);
}

void	ft_execute(char *cmd, char **env)
{
	char	*cmd_path;
	char	**cmd_args;

	cmd_args = ft_split(cmd, ' ');
	cmd_path = find_cmd_path(cmd, env);
	if (!cmd_path)
	{
		ft_free_tab(cmd_args);
		put_error(ERR_CMD);
		write(2, cmd, ft_strlen(cmd));
		write(2, "\n", 1);
		exit(1);
	}
	if (execve(cmd_path, cmd_args, env) == -1)
		put_error(ERR_EXEC);
}
