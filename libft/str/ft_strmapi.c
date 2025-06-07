/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shattori <shattori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 16:27:49 by shattori          #+#    #+#             */
/*   Updated: 2024/11/06 18:07:43 by shattori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	char	*buff;
	int		i;

	i = 0;
	buff = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	while (s[i])
	{
		buff[i] = (*f)(i, s[i]);
		i++;
	}
	buff[i] = '\0';
	return (buff);
}
