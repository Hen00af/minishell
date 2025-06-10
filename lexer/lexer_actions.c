/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nando <nando@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 17:22:25 by nando             #+#    #+#             */
/*   Updated: 2025/06/10 11:37:27 by nando            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	lexer_default(t_lexer *ctx, char c)
{
	ctx->move = 1;
	if (ft_isspace(c))
		append_tok_and_set_state(ctx, QUOTE_NONE, STA_DEFAULT);
	else if (c == '\'')
		append_tok_and_set_state(ctx, QUOTE_NONE, STA_IN_SQUOTE);
	else if (c == '\"')
		append_tok_and_set_state(ctx, QUOTE_NONE, STA_IN_DQUOTE);
	else if (c == '<' || c == '>' || c == '&' || c == '|' || c == '('
		|| c == ')')
		handle_meta(ctx, c);
	else
		buf_add_and_set_state(ctx, c);
}

void	lexer_word(t_lexer *ctx, char c)
{
	ctx->move = 1;
	if (c == '=' && is_valid_var_name(ctx->buf.word))
		buf_add_and_assign_flag(ctx, c);
	else if (c == '<' || c == '>' || c == '&' || c == '|' || c == '('
		|| c == ')')
		handle_meta(ctx, c);
	else if (ft_isspace(c))
	{
		if (ctx->assignment_flag == 1)
		{
			append_token(ctx, TOK_ASSIGN_WORD, QUOTE_NONE,
				buf_flush(&ctx->buf));
			ctx->state = STA_DEFAULT;
		}
		else
			append_tok_and_set_state(ctx, QUOTE_NONE, STA_DEFAULT);
	}
	else if (c == '\'')
		append_tok_and_set_state(ctx, QUOTE_NONE, STA_IN_SQUOTE);
	else if (c == '\"')
		append_tok_and_set_state(ctx, QUOTE_NONE, STA_IN_DQUOTE);
	else if (c == ')')
		append_tok_and_reset_state(ctx, QUOTE_NONE, TOK_RPAREN);
	else
		buf_add_and_set_state(ctx, c);
}

void	lexer_squate(t_lexer *ctx, char c)
{
	ctx->move = 1;
	if (c == '\'')
		append_tok_and_set_state(ctx, QUOTE_SINGLE, STA_DEFAULT);
	else
		buf_add(&ctx->buf, c);
}

void	lexer_dquate(t_lexer *ctx, char c)
{
	ctx->move = 1;
	if (c == '\"')
		append_tok_and_set_state(ctx, QUOTE_DOUBLE, STA_DEFAULT);
	else
		buf_add(&ctx->buf, c);
}
