/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nando <nando@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 17:33:22 by nando             #+#    #+#             */
/*   Updated: 2025/07/25 02:11:57 by nando            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	get_char(int fd)
{
	static char	buf[BUFFER_SIZE];
	static char	*buf_ptr;
	static int	buf_count;

	if (fd < 0)
		return (READ_ERROR);
	if (buf_count <= 0)
	{
		buf_count = read(fd, buf, BUFFER_SIZE);
		if (buf_count < 0)
			return (READ_ERROR);
		buf_ptr = buf;
	}
	if (--buf_count >= 0)
		return (*buf_ptr++);
	else
		return (EOF);
}

static int	add_char_to_string(t_string *str, char c)
{
	char	*new_str;
	size_t	new_capa;

	if (str->len + 1 > str->capa)
	{
		if (str->capa == 0)
			new_capa = 1;
		else
			new_capa = str->capa * 2;
		new_str = (char *)malloc(new_capa * sizeof(char));
		if (!new_str)
			return (MALLOC_ERROR);
		ft_memset(new_str, 0, new_capa);
		if (str->str)
			ft_memcpy(new_str, str->str, str->len);
		free(str->str);
		str->str = new_str;
		str->capa = new_capa;
	}
	str->str[str->len] = c;
	str->len++;
	return (0);
}

static int	make_one_line(int fd, t_string *str)
{
	int	c;

	while (1)
	{
		c = get_char(fd);
		if (c == READ_ERROR)
			return (FAIL);
		if (c == EOF)
			return (0);
		if (add_char_to_string(str, c) == MALLOC_ERROR)
			return (FAIL);
		if (c == '\n')
			return (1);
	}
}

char	*get_next_line(int fd)
{
	t_string	str;
	int			status;

	str.str = NULL;
	str.len = 0;
	str.capa = 0;
	status = make_one_line(fd, &str);
	if (status == FAIL || (status == 0 && str.len == 0))
	{
		free(str.str);
		return (NULL);
	}
	if (add_char_to_string(&str, '\0') == MALLOC_ERROR)
	{
		free(str.str);
		return (NULL);
	}
	return (str.str);
}
