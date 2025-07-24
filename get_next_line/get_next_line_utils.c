/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nando <nando@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 17:11:17 by nando             #+#    #+#             */
/*   Updated: 2025/01/29 17:58:11 by nando            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*cast_src;
	unsigned char	*cast_dest;
	size_t			i;

	i = 0;
	cast_src = (unsigned char *)src;
	cast_dest = (unsigned char *)dest;
	while (i < n)
	{
		cast_dest[i] = cast_src[i];
		i++;
	}
	cast_dest[i] = '\0';
	return (dest);
}

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;
	char	*cast_s;

	i = 0;
	cast_s = (char *)s;
	while (i < n)
	{
		cast_s[i] = c;
		i++;
	}
	return ((void *)cast_s);
}
