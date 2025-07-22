/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shattori <shattori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 20:21:45 by shattori          #+#    #+#             */
/*   Updated: 2025/07/22 11:06:12 by shattori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_ast	*parse_command(t_token **cur)
{
	t_ast	*cmd;
	t_ast	*cmd_leaf;

	cmd = create_empty_command(*cur);
	if (!cmd)
		return (NULL);
	cmd_leaf = cmd;
	while (*cur && (is_redirection_token(*cur) || (*cur)->type == TOK_WORD))
	{
		while (*cur && is_redirection_token(*cur))
		{
			cmd = parse_redirection(cur, cmd);
			if (!cmd)
				return (NULL);
		}
		while (*cur && (*cur)->type == TOK_WORD)
		{
			if (append_argv(cmd_leaf, (*cur)->text))
				return (NULL);
			*cur = (*cur)->next;
		}
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
