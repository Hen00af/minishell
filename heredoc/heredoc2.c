/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nando <nando@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 01:02:08 by nando             #+#    #+#             */
/*   Updated: 2025/07/24 18:04:15 by nando            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"

char	*append_str(char *dst, const char *src)
{
	while (*src)
		*dst++ = *src++;
	return (dst);
}

char	*build_tmp_path(const char *count_str)
{
	size_t	len;
	char	*path;
	char	*p;

	len = ft_strlen("/tmp/heredoc_") + ft_strlen(count_str) + ft_strlen(".tmp")
		+ 1;
	path = malloc(len);
	if (!path)
		return (NULL);
	p = path;
	p = append_str(p, "/tmp/heredoc_");
	p = append_str(p, count_str);
	p = append_str(p, ".tmp");
	*p = '\0';
	return (path);
}

char	*generate_tmpfile_path(void)
{
	static int	g_heredoc_count;
	char		*count_str;
	char		*path;

	count_str = ft_itoa(g_heredoc_count++);
	if (!count_str)
		return (NULL);
	path = build_tmp_path(count_str);
	free(count_str);
	return (path);
}

int	is_include_quote(char *delimiter)
{
	int		len;
	char	start;
	char	end;

	len = ft_strlen(delimiter);
	start = delimiter[0];
	end = delimiter[len - 1];
	if ((start == '\"' && end == '\"') || (start == '\'' && end == '\''))
		return (0);
	return (1);
}
