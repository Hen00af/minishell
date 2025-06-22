/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shattori <shattori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 17:16:10 by nando             #+#    #+#             */
/*   Updated: 2025/06/22 18:53:52 by shattori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

// put token to t_token funk
t_token	*create_token(t_tokentype type, char *word)
{
	t_token	*tok;

	tok = malloc(sizeof * tok);
	if (!tok)
		return (NULL);
	tok->type = type;
	tok->text = word;
	tok->next = NULL;
	return (tok);
}

void	append_token(t_lexer *ctx, t_tokentype type, char *text)
{
	t_token	*tok;

	tok = create_token(type, text);
	if (!tok)
		return ;
	ctx->current->next = tok;
	ctx->current = tok;
}

void	append_tok_and_set_state(t_lexer *ctx, t_statetype state)
{
	if (ctx->buf.len > 0)
		append_token(ctx, TOK_WORD, buf_flush(&ctx->buf));
	ctx->state = state;
}

void	append_tok_and_reset_state(t_lexer *ctx, t_tokentype type)
{
	if (ctx->buf.len > 0)
		append_token(ctx, TOK_WORD, buf_flush(&ctx->buf));
	append_token(ctx, type, NULL);
	ctx->state = STA_DEFAULT;
	if (type == TOK_HEREDOC || type == TOK_REDIR_APP || type == TOK_OR)
		ctx->move = 2;
}

void	free_tokens(t_token *head)
{
	t_token	*next;

	while (head)
	{
		next = head->next;
		if (head->text)
			free(head->text);
		free(head);
		head = next;
	}
}
