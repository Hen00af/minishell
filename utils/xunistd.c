/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xunistd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shattori <shattori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 17:59:17 by shattori          #+#    #+#             */
/*   Updated: 2025/06/30 18:22:26 by shattori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	xdup2(int fildes, int fildes2)
{
	if (dup2(fildes, fildes2) == -1)
	{
		perror("dup2");
	}
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

