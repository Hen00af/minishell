/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shattori <shattori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 23:27:52 by shattori          #+#    #+#             */
/*   Updated: 2024/11/07 19:40:03 by shattori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_in_set(char c, const char *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

int	len_trim(char const *s1, char const *set)
{
	int	start;
	int	end;

	start = 0;
	end = ft_strlen(s1);
	while (s1[start] && is_in_set(s1[start], set))
		start++;
	while (end > start && is_in_set(s1[end - 1], set))
		end--;
	return (end - start);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		len;
	int		start;
	int		i;
	char	*buff;

	if (!s1 || !set)
		return (NULL);
	len = len_trim(s1, set);
	start = 0;
	i = 0;
	while (s1[start] && is_in_set(s1[start], set))
		start++;
	buff = (char *)malloc((len + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	while (i < len)
	{
		buff[i] = s1[start + i];
		i++;
	}
	buff[i] = '\0';
	return (buff);
}
