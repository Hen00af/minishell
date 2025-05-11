/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shattori <shattori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 13:51:38 by shattori          #+#    #+#             */
/*   Updated: 2024/11/07 21:46:36 by shattori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <string.h>

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	dest_len;
	size_t	src_len;
	size_t	max_copy;
	size_t	i;

	src_len = ft_strlen(src);
	if (size == 0)
	{
		return (src_len);
	}
	dest_len = ft_strlen(dest);
	if (dest_len >= size)
	{
		return (size + src_len);
	}
	max_copy = size - dest_len - 1;
	i = 0;
	while (i < max_copy && src[i] != '\0')
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	dest[dest_len + i] = '\0';
	return (dest_len + src_len);
}
