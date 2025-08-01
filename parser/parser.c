/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shattori <shattori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:16:11 by shattori          #+#    #+#             */
/*   Updated: 2025/07/30 07:51:10 by shattori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./parser.h"

t_ast	*parse_pipeline(t_token **cur)
{
	t_ast	*left;
	t_ast	*right;

	left = parse_command_or_subshell(cur);
	if (!left)
		return (NULL);
	while (*cur && (*cur)->type == TOK_PIPE)
	{
		*cur = (*cur)->next;
		right = parse_command_or_subshell(cur);
		if (!right)
		{
			ft_fprintf(STDERROR_INT, "Syntax error after pipe\n");
			return (NULL);
		}
		left = create_ast_node(NODE_PIPE, left, right);
	}
	return (left);
}

t_ast	*parse_subshell(t_token **cur)
{
	t_ast	*inner;
	t_ast	*node;

	if (!*cur || (*cur)->type != TOK_LPAREN)
		return (NULL);
	*cur = (*cur)->next;
	inner = parse_and_or(cur);
	if (!inner)
		return (NULL);
	if (!*cur || (*cur)->type != TOK_RPAREN)
		return (NULL);
	*cur = (*cur)->next;
	node = calloc(1, sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = NODE_SUBSHELL;
	node->left = inner;
	return (node);
}

t_ast	*parse_command_or_subshell(t_token **cur)
{
	t_ast	*cmd;

	if ((*cur)->type == TOK_LPAREN)
		cmd = parse_subshell(cur);
	else
		cmd = parse_command(cur);
	if (!cmd)
		return (NULL);
	while (*cur && ((*cur)->type == TOK_REDIR_IN
			|| (*cur)->type == TOK_REDIR_OUT || (*cur)->type == TOK_REDIR_APP
			|| (*cur)->type == TOK_HEREDOC))
	{
		cmd = parse_redirection(cur, cmd);
		if (!cmd)
			return (NULL);
	}
	return (cmd);
}

t_ast	*parse_redirection(t_token **cur, t_ast *cmd)
{
	t_node_type	type;
	t_ast		*redir;

	if ((*cur)->type == TOK_REDIR_IN)
		type = NODE_REDIR_IN;
	else if ((*cur)->type == TOK_REDIR_OUT)
		type = NODE_REDIR_OUT;
	else if ((*cur)->type == TOK_REDIR_APP)
		type = NODE_REDIR_APPEND;
	else if ((*cur)->type == TOK_HEREDOC)
		type = NODE_HEREDOC;
	else
		return (NULL);
	*cur = (*cur)->next;
	if (!*cur || (*cur)->type != TOK_WORD || !(*cur)->text)
		return (NULL);
	redir = calloc(1, sizeof(t_ast));
	if (!redir)
		return (NULL);
	redir->type = type;
	redir->filename = ft_strdup((*cur)->text);
	redir->left = cmd;
	redir->right = NULL;
	*cur = (*cur)->next;
	return (redir);
}

t_ast	*create_ast_node(t_node_type type, t_ast *left, t_ast *right)
{
	t_ast	*node;

	node = calloc(1, sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = type;
	node->left = left;
	node->right = right;
	return (node);
}
