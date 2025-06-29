/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shattori <shattori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 20:21:45 by shattori          #+#    #+#             */
/*   Updated: 2025/06/29 16:37:10 by shattori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	is_redirection_token(t_token *tok)
{
	if (!tok)
		return (0);
	return (tok->type == TOK_REDIR_IN || tok->type == TOK_REDIR_OUT
		|| tok->type == TOK_REDIR_APPEND || tok->type == TOK_HEREDOC);
}

t_ast	*parse_simple_command(t_token **cur)
{
	t_token	*tok;
	t_ast	*cmd;
	int		i;
	int		argc;

	i = 0;
	argc = 0;
	tok = *cur;
	while (tok && tok->type == TOK_WORD && argc++ >= 0)
		tok = tok->next;
	if (argc == 0)
		return (NULL);
	cmd = ft_calloc(1, sizeof(t_ast));
	cmd->type = NODE_COMMAND;
	cmd->argv = ft_calloc(argc + 1, sizeof(char *));
	while (i < argc)
	{
		cmd->argv[i++] = ft_strdup((*cur)->text);
		*cur = (*cur)->next;
	}
	return (cmd);
}

t_ast	*parse_command(t_token **cur)
{
	t_ast	*cmd;

	cmd = parse_simple_command(cur);
	if (!cmd)
		return (NULL);
	while (*cur && is_redirection_token(*cur))
	{
		cmd = parse_redirection(cur, cmd);
		if (!cmd)
			return (NULL);
	}
	return (cmd);
}

t_ast	*parse_and_or(t_token **cur)
{
	t_ast		*left;
	t_node_type	op_type;
	t_ast		*right;

	left = parse_pipeline(cur);
	if (!left)
		return (NULL);
	while (*cur && ((*cur)->type == TOK_AND || (*cur)->type == TOK_OR))
	{
		if ((*cur)->type == TOK_AND)
			op_type = NODE_AND;
		else
			op_type = NODE_OR;
		*cur = (*cur)->next;
		right = parse_pipeline(cur);
		if (!right)
			return (NULL);
		left = create_ast_node(op_type, left, right);
	}
	return (left);
}

t_ast	*start_parse(t_token *tokens)
{
	t_token	*cur;

	if (tokens == NULL)
		return (NULL);
	cur = tokens;
	return (parse_and_or(&cur));
}
