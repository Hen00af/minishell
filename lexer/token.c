/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nando <nando@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 17:16:10 by nando             #+#    #+#             */
/*   Updated: 2025/06/08 22:25:50 by nando            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_token	*create_token(TokenType type, QuoteType q_type, char *word)
{
	t_token	*tok;

	tok = malloc(sizeof *tok);
	if (!tok)
		return (NULL);
	tok->type = type;
	tok->quote_type = q_type;
	tok->text = word;
	tok->next = NULL;
	return (tok);
}

void	append_token(t_lexer *ctx, TokenType type, QuoteType q_type, char *text)
{
	t_token	*tok;

	tok = create_token(type, q_type, text);
	if (!tok)
		return ;
	ctx->current->next = tok;
	ctx->current = tok;
}

void	append_tok_and_set_state(t_lexer *ctx, QuoteType q_type,
		StateType state)
{
	if (ctx->buf.len > 0)
		append_token(ctx, TOK_WORD, q_type, buf_flush(&ctx->buf));
	ctx->state = state;
}

void	append_tok_and_reset_state(t_lexer *ctx, QuoteType q_type,
		TokenType type)
{
	if (ctx->buf.len > 0)
		append_token(ctx, TOK_WORD, q_type, buf_flush(&ctx->buf));
	append_token(ctx, type, QUOTE_NONE, NULL);
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
