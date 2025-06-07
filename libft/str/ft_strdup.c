/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shattori <shattori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 13:51:36 by shattori          #+#    #+#             */
/*   Updated: 2024/11/13 20:49:23 by shattori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*ret;
	size_t	len;

	len = ft_strlen(s1);
	ret = malloc((len + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	ft_strlcpy(ret, s1, len + 1);
	return (ret);
}
