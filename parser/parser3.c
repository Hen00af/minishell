/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shattori <shattori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 11:06:15 by shattori          #+#    #+#             */
/*   Updated: 2025/07/24 17:24:32 by shattori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	is_redirection_token(t_token *tok)
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

	(void)cur;
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

