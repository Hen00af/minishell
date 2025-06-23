/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shattori <shattori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 15:41:26 by shattori          #+#    #+#             */
/*   Updated: 2025/06/21 15:30:35 by shattori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	is_charset(char c, char *charset)
{
	int	i;

	i = 0;
	while (charset[i])
		if (c == charset[i++])
			return (1);
	return (0);
}

int	word_count(char *str, char *charset)
{
	int	count;
	int	in_word;
	int	i;

	count = 0;
	in_word = 0;
	i = 0;
	while (str[i])
	{
		if (is_charset(str[i], charset))
			in_word = 0;
		else if (!in_word)
		{
			in_word = 1;
			count++;
		}
		i++;
	}
	return (count);
}

char	*ft_strndup(char *src, int n)
{
	char	*dest;
	int		i;

	dest = (char *)malloc((n + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	i = 0;
	while (i < n)
	{
		dest[i] = src[i];
		i++;
	}
	dest[n] = '\0';
	return (dest);
}

void	split_words(char **result, char *str, char *charset)
{
	int	start;
	int	i;
	int	count;

	start = -1;
	count = 0;
	i = 0;
	while (str[i])
	{
		if (is_charset(str[i], charset))
		{
			if (start != -1)
				result[count++] = ft_strndup(str + start, i - start);
			start = -1;
		}
		else if (start == -1)
			start = i;
		i++;
	}
	if (start != -1)
		result[count++] = ft_strndup(str + start, i - start);
	result[count] = NULL;
}

char	**ft_split(char *str, char *charset)
{
	char	**result;
	int		count;

	count = word_count(str, charset);
	result = (char **)malloc((count + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	split_words(result, str, charset);
	return (result);
}
