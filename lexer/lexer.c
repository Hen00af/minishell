/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nando <nando@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 20:23:45 by nando             #+#    #+#             */
/*   Updated: 2025/07/19 18:37:03 by nando            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	handle_meta(t_lexer *ctx, char c)
{
	char	next;

	next = ctx->input[ctx->posi + 1];
	if (c == '<' && next == '<')
		append_tok_and_reset_state(ctx, TOK_HEREDOC);
	else if (c == '>' && next == '>')
		append_tok_and_reset_state(ctx, TOK_REDIR_APP);
	else if (c == '|' && next == '|')
		append_tok_and_reset_state(ctx, TOK_OR);
	else if (c == '&' && next == '&')
		append_tok_and_reset_state(ctx, TOK_AND);
	else if (c == '<')
		append_tok_and_reset_state(ctx, TOK_REDIR_IN);
	else if (c == '>')
		append_tok_and_reset_state(ctx, TOK_REDIR_OUT);
	else if (c == '|')
		append_tok_and_reset_state(ctx, TOK_PIPE);
	else if (c == '(')
		append_tok_and_reset_state(ctx, TOK_LPAREN);
	else if (c == ')')
		append_tok_and_reset_state(ctx, TOK_RPAREN);
}

int	init_lexer(t_lexer *ctx, char *input)
{
	buf_init(&ctx->buf);
	if (!ctx->buf.word)
		return (ERROR);
	ctx->input = input;
	ctx->state = STA_DEFAULT;
	ctx->prev_state = STA_DEFAULT;
	ctx->posi = 0;
	ctx->assignment_flag = 0;
	ctx->left_p_count = 0;
	ctx->right_p_count = 0;
	ctx->head = create_token(TOK_NUL, NULL);
	if (!ctx->head)
		return (ERROR);
	ctx->current = ctx->head;
	return (0);
}

//　start run
void	run_lexer(t_lexer *ctx)
{
	char	c;

	c = ctx->input[ctx->posi];
	ctx->move = 1;
	if (ctx->state == STA_DEFAULT)
		lexer_default(ctx, c);
	else if (ctx->state == STA_IN_WORD)
		lexer_word(ctx, c);
	else if (ctx->state == STA_IN_SQUOTE)
		lexer_squate(ctx, c);
	else if (ctx->state == STA_IN_DQUOTE)
		lexer_dquate(ctx, c);
	ctx->posi = ctx->posi + ctx->move;
}

t_token	*finish_lexing(t_lexer *ctx)
{
	t_token	*token_head;

	if (ctx->buf.len > 0)
	{
		if (ctx->assignment_flag == 0)
			append_token(ctx, TOK_WORD, buf_flush(&ctx->buf));
		else
			append_token(ctx, TOK_ASSIGN_WORD, buf_flush(&ctx->buf));
	}
	append_token(ctx, TOK_EOF, NULL);
	token_head = ctx->head->next;
	free_buf(&ctx->buf);
	free(ctx->head);
	adjust_assign_word(token_head);
	return (token_head);
}

t_token	*lexer(char *input)
{
	t_lexer	ctx;
	t_token	*token_head;
	char	c;

	if (init_lexer(&ctx, input) == ERROR)
		return (NULL);
	c = ctx.input[ctx.posi];
	while (ctx.input[ctx.posi])
		run_lexer(&ctx);
	if (ctx.state == STA_IN_SQUOTE || ctx.state == STA_IN_DQUOTE)
	{
		quate_error(&ctx);
		return (NULL);
	}
	if (ctx.left_p_count != ctx.right_p_count)
	{
		parent_error(&ctx);
		return (NULL);
	}
	token_head = finish_lexing(&ctx);
	return (token_head);
}
