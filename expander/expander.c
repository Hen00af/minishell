/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nando <nando@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 14:30:21 by nando             #+#    #+#             */
/*   Updated: 2025/06/26 21:01:22 by nando            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

void	expand_andor_arguments(t_andor *ast, t_env *env);

char	*expand_string(char *arg, t_env *env, t_expand *ctx, t_list *node)
{
	char			*cleaned_quote;
	char			*before;
	t_redirection	*redir;

	redir = (t_redirection *)node->content;
	if (arg[0] == '\'')
	{
		cleaned_quote = remove_quote(redir->need_expand, arg);
		return (cleaned_quote);
	}
	else if (arg[0] == '\"')
	{
		cleaned_quote = remove_quote(redir->need_expand, arg);
		cleaned_quote = expand_variables(cleaned_quote, env);
		return (cleaned_quote);
	}
	redir->need_expand = false;
	before = ft_strdup(arg);
	expand_all_type(arg, env);
	if (strcmp(before, arg) != 0)
		ctx->wild_flag = 1;
	free(before);
	return (ft_strdup(arg));
}

void	expand_command_args(t_command *cmd, t_env *env, t_list *cmd_list)
{
	t_expand	ctx;
	int			i;

	i = 0;
	if (cmd && cmd->argv[i])
	{
		while (cmd->argv && cmd->argv[i])
		{
			ctx.wild_flag = 0;
			ctx.expanded = expand_string(cmd->argv[i], env, &ctx, cmd_list);
			if (ctx.wild_flag)
			{
				generate_wildcard_matches(&ctx, cmd, &i);
				continue ;
			}
			free(cmd->argv[i]);
			cmd->argv[i] = ft_strdup(ctx.expanded);
			ctx.expanded = NULL;
			i++;
		}
	}
}

void	expander(t_andor *ast, t_env *env)
{
	t_list		*cmd_node;
	t_command	*cmd;

	if (!ast || ast->type != ANDOR_PIPELINE)
		return ;
	if (!ast->pipeline || !ast->pipeline->commands)
		return ;
	cmd_node = ast->pipeline->commands;
	while (cmd_node)
	{
		cmd = (t_command *)cmd_node->content;
		if (cmd->argv && cmd->argv[0])
			expand_command_args(cmd, env, ast->pipeline->commands);
		if (cmd->subshell_ast)
			expand_andor_arguments(cmd->subshell_ast, env);
		cmd_node = cmd_node->next;
	}
}

void	expand_andor_arguments(t_andor *ast, t_env *env)
{
	if (!ast)
		return ;
	if (ast->type == ANDOR_PIPELINE)
		expander(ast, env);
	else if (ast->type == ANDOR_AND || ast->type == ANDOR_OR)
	{
		expand_andor_arguments(ast->left, env);
		expand_andor_arguments(ast->right, env);
	}
}
