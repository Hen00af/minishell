/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shattori <shattori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 11:07:27 by shattori          #+#    #+#             */
/*   Updated: 2025/08/01 15:06:31 by shattori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <stdio.h>
#include <unistd.h>

int	print_syntax_error(const char *token_text, t_tokentype type)
{
	if (type == TOK_WORD)
	{
		if (token_text)
			ft_fprintf(2,
				"minishell: syntax error near unexpected token `%s'\n",
				token_text);
		else
			ft_fprintf(2,
				"minishell: syntax error near unexpected token `newline'\n");
	}
	else if (type == TOK_REDIR_IN)
		ft_fprintf(2, "minishell: syntax error near unexpected token `<'\n");
	else if (type == TOK_REDIR_OUT)
		ft_fprintf(2, "minishell: syntax error near unexpected token `>'\n");
	else if (type == TOK_REDIR_APP)
		ft_fprintf(2, "minishell: syntax error near unexpected token `>>'\n");
	else if (type == TOK_HEREDOC)
		ft_fprintf(2, "minishell: syntax error near unexpected token `<<'\n");
	else if (type == TOK_PIPE)
		ft_fprintf(2, "minishell: syntax error near unexpected token `|'\n");
	return (258);
}

int	check_pipe_syntax(t_token *tok, t_token *prev)
{
	if (!prev || !tok->next)
		return (print_syntax_error("|", tok->type));
	if (prev->type != TOK_WORD && prev->type != TOK_RPAREN)
		return (print_syntax_error("|", tok->type));
	if (tok->next->type != TOK_WORD && tok->next->type != TOK_LPAREN
		&& tok->next->type != TOK_REDIR_APP && tok->next->type != TOK_REDIR_IN
		&& tok->next->type != TOK_REDIR_OUT && tok->next->type != TOK_HEREDOC)
		return (print_syntax_error("|", tok->type));
	return (0);
}

int	check_redir_syntax(t_token *tok)
{
	if (!tok->next)
		return (print_syntax_error("newline", TOK_WORD));
	if (tok->next->type != TOK_WORD && tok->next->type != TOK_ASSIGN_WORD
		&& tok->next->type != TOK_RPAREN)
		return (print_syntax_error(tok->next->text, tok->type));
	return (0);
}

int	check_andor_syntax(t_token *tok, t_token *prev)
{
	if (!prev || !tok->next)
		return (print_syntax_error(NULL, tok->type));
	if ((prev->type != TOK_WORD && prev->type != TOK_RPAREN)
		|| (tok->next->type != TOK_WORD && tok->next->type != TOK_LPAREN))
		return (print_syntax_error(NULL, tok->type));
	return (0);
}

void	has_syntax_error(t_token *tok, t_shell *shell)
{
	t_token	*prev;

	prev = NULL;
	while (tok && tok->type != TOK_EOF)
	{
		// パイプの先にリダイレクションがあった場合の処理　実装する
		if (tok->type == TOK_PIPE)
		{
			if (check_pipe_syntax(tok, prev))
				shell->exit_status = 258;
		}
		if (tok->type == TOK_REDIR_IN || tok->type == TOK_REDIR_OUT
			|| tok->type == TOK_REDIR_APP || tok->type == TOK_HEREDOC)
		{
			if (check_redir_syntax(tok))
				shell->exit_status = 258;
		}
		else if (tok->type == TOK_AND || tok->type == TOK_OR)
		{
			if (check_andor_syntax(tok, prev))
				shell->exit_status = 258;
		}
		prev = tok;
		tok = tok->next;
	}
}
