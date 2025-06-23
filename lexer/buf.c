/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shattori <shattori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:31:47 by nando             #+#    #+#             */
/*   Updated: 2025/06/22 20:21:06 by shattori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	buf_init(t_buf *buf)
{
	buf->capa = 1;
	buf->len = 0;
	buf->word = malloc(buf->capa * sizeof(*buf->word));
	if (!buf->word)
		return ;
	if (buf->word)
		buf->word[0] = '\0';
}

void	buf_add(t_buf *buf, char c)
{
	char	*new_word;
	size_t	new_capa;

	if (buf->capa <= (buf->len + 1))
	{
		new_capa = buf->capa * 2;
		new_word = malloc(new_capa);
		if (!new_word)
			return ;
		ft_memcpy(new_word, buf->word, buf->len);
		free(buf->word);
		buf->word = new_word;
		buf->capa = new_capa;
	}
	buf->word[buf->len++] = c;
	buf->word[buf->len] = '\0';
}

// flush bufer and return str content
char	*buf_flush(t_buf *buf)
{
	char	*text;

	text = buf->word;
	buf_init(buf);
	if (!buf->word)
		return (NULL);
	return (text);
}

void	free_buf(t_buf *buf)
{
	if (buf->word)
		free(buf->word);
}
