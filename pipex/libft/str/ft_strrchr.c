/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shattori <shattori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 13:51:49 by shattori          #+#    #+#             */
/*   Updated: 2024/10/29 19:50:08 by shattori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	char	*locate;

	locate = NULL;
	while (*str)
	{
		if (*str == (char)c)
			locate = (char *)str;
		str++;
	}
	if (c == '\0')
		return ((char *)str);
	return (locate);
}
