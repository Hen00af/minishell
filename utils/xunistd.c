/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xunistd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shattori <shattori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 17:59:17 by shattori          #+#    #+#             */
/*   Updated: 2025/07/24 17:15:19 by shattori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	xdup2(int fildes, int fildes2)
{
	if (dup2(fildes, fildes2) == -1)
		perror("dup2");
	xclose(&fildes);
}

int	xclose(int *fd)
{
	int	ret;

	if (!fd || *fd < 3)
		return (0);
	ret = close(*fd);
	if (ret == -1)
		perror("close");
	*fd = -1;
	return (ret);
}

void	xfree(void **ptr)
{
	if (!ptr || *ptr == NULL)
		return ;
	free(*ptr);
	*ptr = NULL;
}

int	xopen(const char *file, int oflag, mode_t mode, int *fd)
{
	*fd = open(file, oflag, mode);
	if (*fd == -1)
	{
		perror("open");
		return (-1);
	}
	return (0);
}
