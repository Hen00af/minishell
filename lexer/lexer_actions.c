/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nando <nando@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 17:22:25 by nando             #+#    #+#             */
/*   Updated: 2025/05/29 19:49:12 by nando            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	lexer_default(t_lexer *ctx, char c)
{
	ctx->move = 1;
	if (ft_isspace(c))
		append_tok_and_set_state(ctx, STA_DEFAULT);
	else if (c == '\'')
		append_tok_and_set_state(ctx, STA_IN_SQUOTE);
	else if (c == '\"')
		append_tok_and_set_state(ctx, STA_IN_DQUOTE);
	else if (c == '<' || c == '>' || c == '&' || c == '|' || c == '('
		|| c == ')')
		handle_meta(ctx, c);
	else
		buf_add_and_set_state(ctx, c);
}

void	lexer_word(t_lexer *ctx, char c)
{
	ctx->move = 1;
	if (ft_isspace(c))
		append_tok_and_set_state(ctx, STA_DEFAULT);
	else if (c == '\'')
		append_tok_and_set_state(ctx, STA_IN_SQUOTE);
	else if (c == '\"')
		append_tok_and_set_state(ctx, STA_IN_DQUOTE);
	else if (c == '$')
		append_tok_and_set_state(ctx, STA_IN_VARIABLE);
	else if (c == ')')
		append_tok_and_reset_state(ctx, TOK_RPAREN);
	else
		buf_add_and_set_state(ctx, c);
}

void	lexer_squate(t_lexer *ctx, char c)
{
	ctx->move = 1;
	if (c == '\'')
		ctx->state = STA_DEFAULT;
	else
		buf_add(&ctx->buf, c);
}

void	lexer_dquate(t_lexer *ctx, char c)
{
	ctx->move = 1;
	if (c == '\"')
		append_tok_and_set_state(ctx, STA_DEFAULT);
	else if (c == '$')
	{
		append_tok_and_set_state(ctx, STA_IN_VARIABLE);
		ctx->prev_state = STA_IN_DQUOTE;
		buf_add(&ctx->buf, c);
	}
	else
		buf_add(&ctx->buf, c);
}

void	lexer_variable(t_lexer *ctx, char c)
{
	ctx->move = 1;
	if (isalnum(c) || c == '_' || c == '?')
		buf_add(&ctx->buf, c);
	else
	{
		append_token(ctx, TOK_VARIABLE, buf_flush(&ctx->buf));
		if (ctx->prev_state == STA_IN_DQUOTE)
		{
			ctx->state = ctx->prev_state;
			ctx->prev_state = STA_DEFAULT;
		}
		ctx->move = 0;
	}
}
