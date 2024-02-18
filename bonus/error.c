/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbazaz <fbazaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 10:22:34 by fbazaz            #+#    #+#             */
/*   Updated: 2024/02/17 10:01:45 by fbazaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	p_error(char *err)
{
	perror(err);
	exit(1);
}

int	put_error(char *err)
{
	write(2, err, ft_strlen(err));
	return (1);
}
