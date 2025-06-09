/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nando <nando@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 20:23:45 by nando             #+#    #+#             */
/*   Updated: 2025/06/09 13:51:22 by nando            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

void	handle_meta(t_lexer *ctx, char c)
{
	char	next;

	next = ctx->input[ctx->posi + 1];
	if (c == '<' && next == '<')
		append_tok_and_reset_state(ctx, QUOTE_NONE, TOK_HEREDOC);
	else if (c == '>' && next == '>')
		append_tok_and_reset_state(ctx, QUOTE_NONE, TOK_REDIR_APP);
	else if (c == '|' && next == '|')
		append_tok_and_reset_state(ctx, QUOTE_NONE, TOK_OR);
	else if (c == '&' && next == '&')
		append_tok_and_reset_state(ctx, QUOTE_NONE, TOK_AND);
	else if (c == '<')
		append_tok_and_reset_state(ctx, QUOTE_NONE, TOK_REDIR_IN);
	else if (c == '>')
		append_tok_and_reset_state(ctx, QUOTE_NONE, TOK_REDIR_OUT);
	else if (c == '|')
		append_tok_and_reset_state(ctx, QUOTE_NONE, TOK_PIPE);
	else if (c == '(')
		append_tok_and_reset_state(ctx, QUOTE_NONE, TOK_LPAREN);
	else if (c == ')')
		append_tok_and_reset_state(ctx, QUOTE_NONE, TOK_RPAREN);
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
	ctx->head = create_token(TOK_NUL, QUOTE_NONE, NULL);
	if (!ctx->head)
		return (ERROR);
	ctx->current = ctx->head;
	return (0);
}

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
		append_token(ctx, TOK_WORD, QUOTE_NONE, buf_flush(&ctx->buf));
	append_token(ctx, TOK_EOF, QUOTE_NONE, NULL);
	token_head = ctx->head->next;
	free_buf(&ctx->buf);
	free(ctx->head);
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
	token_head = finish_lexing(&ctx);
	return (token_head);
}

int	main(int argc, char **argv)
{
	t_token		*tokens;
	const char	*display_text;
	char		tmp[32];

	if (argc < 2)
	{
		fprintf(stderr, "Usage: %s \"input string\"\n", argv[0]);
		return (EXIT_FAILURE);
	}
	printf("Test input: %s\n", argv[1]);
	tokens = lexer(argv[1]);
	if (!tokens)
	{
		fprintf(stderr, "Lexer error.\n");
		return (EXIT_FAILURE);
	}
	printf("Tokens:\n");
	for (t_token *tok = tokens; tok != NULL; tok = tok->next)
	{
		display_text = tok->text;
		if (display_text == NULL)
		{
			snprintf(tmp, sizeof(tmp), "(NULL)");
			display_text = tmp;
		}
		printf("  [Type=%d] [Quote = %d] '%s'\n", tok->type, tok->quote_type,
			display_text);
	}
	free_tokens(tokens);
	return (EXIT_SUCCESS);
}
