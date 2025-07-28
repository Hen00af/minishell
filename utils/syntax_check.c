/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shattori <shattori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 11:07:27 by shattori          #+#    #+#             */
/*   Updated: 2025/07/28 12:00:07 by shattori         ###   ########.fr       */
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

int	has_syntax_error(t_token *tok)
{
	t_token	*prev;

	prev = NULL;
	while (tok && tok->type != TOK_EOF)
	{
		if (tok->type == TOK_PIPE)
		{
			if (!prev || !tok->next || !(tok->next->type == TOK_WORD)
				|| !(prev->type == TOK_WORD))
				return (print_syntax_error("|", tok->type));
		}
		else if (tok->type == TOK_REDIR_IN || tok->type == TOK_REDIR_OUT
			|| tok->type == TOK_REDIR_APP || tok->type == TOK_HEREDOC)
		{
			if (!tok->next)
				return (print_syntax_error("newline", TOK_WORD));
			if (tok->next->type != TOK_WORD
				&& tok->next->type != TOK_ASSIGN_WORD)
				return (print_syntax_error(tok->next->text, tok->next->type));
		}
		prev = tok;
		tok = tok->next;
	}
	return (0);
}
