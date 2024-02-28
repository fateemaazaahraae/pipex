/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbazaz <fbazaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 12:05:29 by fbazaz            #+#    #+#             */
/*   Updated: 2024/02/26 12:27:05 by fbazaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	ft_putendl_fd(char *s, char *cmd, int fd, int status)
{
	int	i;
	int	j;

	if (fd < 0)
		return ;
	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
	if (cmd)
	{
		j = 0;
		while (cmd[j])
		{
			write(fd, &cmd[j], 1);
			j++;
		}
	}
	write(fd, "\n", 1);
	if (status != -1)
		exit(status);
	return ;
}
