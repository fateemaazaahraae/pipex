/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbazaz <fbazaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 09:52:11 by fbazaz            #+#    #+#             */
/*   Updated: 2024/02/24 14:00:37 by fbazaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*ft_read_line(int fd, char *str)
{
	char	*buffer;
	int		read_bytes;

	buffer = (char *)malloc(BUFFER_SIZE + 1 * sizeof(char));
	if (!buffer)
		return (free(str), NULL);
	read_bytes = 1;
	while (read_bytes > 0)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes == -1)
			return (free(buffer), free(str), NULL);
		buffer[read_bytes] = '\0';
		str = ft_strjoin(str, buffer);
		if (ft_strchr(str, '\n'))
			break ;
	}
	return (free(buffer), str);
}

char	*ft_fill(char *str)
{
	char	*p;
	int		i;

	i = 0;
	p = NULL;
	if (!str || str[0] == '\0')
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	p = (char *)malloc(sizeof(char) * (i + 2));
	if (!p)
		return (free(str), NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		p[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
	{
		p[i] = str[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

char	*ft_new_str(char *str)
{
	char	*p;
	int		i;
	int		j;

	i = 0;
	p = NULL;
	if (!str || str[0] == '\0')
		return (free(str), NULL);
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
		return (free(str), NULL);
	p = (char *)malloc(sizeof(char) * (ft_strlen(str) - i + 1));
	if (!p)
		return (free(str), NULL);
	i++;
	j = 0;
	while (str[i])
		p[j++] = str[i++];
	p[j] = '\0';
	return (free(str), p);
}

char	*get_next_line(int fd, int ac)
{
	static char	*str;
	char		*line;
	int			i;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	i = 3;
	while (i < ac - 2)
	{
		write(1, "pipe ", 5);
		i++;
	}
	write(1, "heredoc> ", 9);
	str = ft_read_line(fd, str);
	if (!str)
		return (NULL);
	line = ft_fill(str);
	str = ft_new_str(str);
	return (line);
}
