/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shattori <shattori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 14:16:07 by shattori          #+#    #+#             */
/*   Updated: 2024/11/05 15:47:46 by shattori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			cnt;
	unsigned char	uc;

	uc = (unsigned char)c;
	cnt = 0;
	while (cnt < len)
	{
		*((unsigned char *)b + cnt) = uc;
		cnt++;
	}
	return (b);
}
