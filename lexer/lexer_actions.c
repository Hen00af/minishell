/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nando <nando@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 17:22:25 by nando             #+#    #+#             */
/*   Updated: 2025/06/26 15:23:14 by nando            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

// identify and sepalate using spaces and special characters.
// and add token state
void	lexer_default(t_lexer *ctx, char c)
{
	ctx->move = 1;
	if (ft_isspace(c))
		append_tok_and_set_state(ctx, STA_DEFAULT);
	else if (c == '\'')
	{
		append_tok_and_set_state(ctx, STA_IN_SQUOTE);
		buf_add(&ctx->buf, c);
	}
	else if (c == '\"')
	{
		append_tok_and_set_state(ctx, STA_IN_DQUOTE);
		buf_add(&ctx->buf, c);
	}
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
	{
		buf_add_and_assign_flag(ctx, c);
		return ;
	}
	else if (c == '<' || c == '>' || c == '&' || c == '|' || c == '('
		|| c == ')')
	{
		handle_meta(ctx, c);
		return ;
	}
	else if (ft_isspace(c))
	{
		if (ctx->assignment_flag == 1)
		{
			append_token(ctx, TOK_ASSIGN_WORD, buf_flush(&ctx->buf));
			ctx->state = STA_DEFAULT;
		}
		else
			append_tok_and_set_state(ctx, STA_DEFAULT);
		return ;
	}
	lexer_word2(ctx, c);
}

void	lexer_word2(t_lexer *ctx, char c)
{
	if (c == '\'')
	{
		append_tok_and_set_state(ctx, STA_IN_SQUOTE);
		buf_add(&ctx->buf, c);
	}
	else if (c == '\"')
	{
		append_tok_and_set_state(ctx, STA_IN_DQUOTE);
		buf_add(&ctx->buf, c);
	}
	else if (c == ')')
		append_tok_and_reset_state(ctx, TOK_RPAREN);
	else
		buf_add_and_set_state(ctx, c);
}

void	lexer_squate(t_lexer *ctx, char c)
{
	ctx->move = 1;
	if (c == '\'')
	{
		buf_add(&ctx->buf, c);
		append_tok_and_set_state(ctx, STA_DEFAULT);
	}
	else
		buf_add(&ctx->buf, c);
}

void	lexer_dquate(t_lexer *ctx, char c)
{
	ctx->move = 1;
	if (c == '\"')
	{
		buf_add(&ctx->buf, c);
		append_tok_and_set_state(ctx, STA_DEFAULT);
	}
	else
		buf_add(&ctx->buf, c);
}
