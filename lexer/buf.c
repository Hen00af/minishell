/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nando <nando@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:31:47 by nando             #+#    #+#             */
/*   Updated: 2025/06/05 16:52:55 by nando            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	buf_init(t_buf *buf)
{
	buf->capa = 1;
	buf->len = 0;
	buf->word = malloc(buf->capa * sizeof *buf->word);
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
		memcpy(new_word, buf->word, buf->len);
		free(buf->word);
		buf->word = new_word;
		buf->capa = new_capa;
	}
	buf->word[buf->len++] = c;
	buf->word[buf->len] = '\0';
}

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

void	buf_add_and_assign_flag(t_lexer *ctx, char c)
{
	buf_add(&ctx->buf, c);
	ctx->assignment_flag = 1;
}

void	buf_add_and_set_state(t_lexer *ctx, char c)
{
	buf_add(&ctx->buf, c);
	ctx->state = STA_IN_WORD;
}
