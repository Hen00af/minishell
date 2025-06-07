/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shattori <shattori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 18:00:45 by shattori          #+#    #+#             */
/*   Updated: 2024/11/07 18:51:42 by shattori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t count)
{
	const unsigned char	*_buf1;
	const unsigned char	*_buf2;

	_buf1 = (const unsigned char *)s1;
	_buf2 = (const unsigned char *)s2;
	while (count--)
	{
		if (*_buf1 != *_buf2)
			return (*_buf1 - *_buf2);
		_buf1++;
		_buf2++;
	}
	return (0);
}
