/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 14:16:03 by shattori          #+#    #+#             */
/*   Updated: 2025/02/11 16:54:09 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, unsigned int count)
{
	char	*dptr;
	char	*sptr;
	int		cnt;

	cnt = 0;
	if (!dst && !src)
		return (NULL);
	cnt = 0;
	if (dst > src)
	{
		dptr = (char *)dst + count - 1;
		sptr = (char *)src + count - 1;
		while (count--)
			*dptr-- = *sptr--;
	}
	else
	{
		dptr = (char *)dst;
		sptr = (char *)src;
		while (count--)
			*dptr++ = *sptr++;
	}
	return (dst);
}
