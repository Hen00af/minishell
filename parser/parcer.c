/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shattori <shattori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 20:21:45 by shattori          #+#    #+#             */
/*   Updated: 2025/07/09 15:03:21 by shattori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	is_redirection_token(t_token *tok)
{
	if (!tok)
		return (0);
	return (tok->type == TOK_REDIR_IN || tok->type == TOK_REDIR_OUT
		|| tok->type == TOK_REDIR_APP || tok->type == TOK_HEREDOC);
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

t_ast	*create_empty_command(t_token *cur)
{
	t_ast	*cmd;

	cmd = ft_calloc(1, sizeof(t_ast));
	if (!cmd)
		return (NULL);
	cmd->type = NODE_COMMAND;
	cmd->argv = ft_calloc(1, sizeof(char *));
	if (!cmd->argv)
	{
		free(cmd);
		return (NULL);
	}
	cmd->argv[0] = NULL;
	return (cmd);
}
t_ast	*first_redirection(t_token **cur)
{
	t_ast	*cmd;

	if (!(*cur) || !(*cur)->next)
		return (NULL);
	cmd = create_empty_command((*cur));
	if (!cmd)
		return (NULL);
	cmd = parse_redirection(cur, cmd);
	if (!cmd)
		return (NULL);
	printf("\nenter frider\n");
	if (*cur && (*cur)->type == TOK_WORD)
	{
		free(cmd->argv);
		cmd->argv = ft_calloc(2, sizeof(char *));
		if (!cmd->argv)
		{
			free(cmd);
			return (NULL);
		}
		cmd->argv[0] = ft_strdup((*cur)->text);
		cmd->argv[1] = NULL;
		*cur = (*cur)->next;
	}
	return (cmd);
}

int	append_argv(t_ast *cmd, char *word)
{
	int		argc;
	char	**new_argv;

	argc = 0;
	printf("enter funk");
	while (cmd->argv && cmd->argv[argc])
		argc++;
	new_argv = ft_calloc(argc + 2, sizeof(char *));
	if (!new_argv)
		return (1);
	for (int i = 0; i < argc; i++)
		new_argv[i] = ft_strdup(cmd->argv[i]);
	new_argv[argc] = ft_strdup(word);
	new_argv[argc + 1] = NULL;
	for (int i = 0; i < argc; i++)
		free(cmd->argv[i]);
	free(cmd->argv);
	cmd->argv = new_argv;
	return (0);
}

t_ast	*parse_command(t_token **cur)
{
	t_ast	*cmd;

	cmd = create_empty_command(*cur);
	if (!cmd)
		return (NULL);
	while (*cur && is_redirection_token(*cur))
	{
		cmd = parse_redirection(cur, cmd);
		if (!cmd)
			return (NULL);
	}
	while (*cur && (*cur)->type == TOK_WORD)
	{
		if (append_argv(cmd, (*cur)->text))
			return (NULL);
		*cur = (*cur)->next;
	}
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
