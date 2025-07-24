/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nando <nando@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 14:30:21 by nando             #+#    #+#             */
/*   Updated: 2025/07/24 18:00:24 by nando            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

void	expand_andor_arguments(t_andor *ast, t_shell *shell);

void	run_expand(char c, t_shell *shell, t_expand *ctx)
{
	if (ctx->state == STA_NONE_Q && c == '\"')
		expand_and_add_to_output(ctx, shell, STA_DOUBLE_Q, 1);
	else if (ctx->state == STA_NONE_Q && c == '\'')
		expand_and_add_to_output(ctx, shell, STA_SINGLE_Q, 2);
	else if (ctx->state == STA_DOUBLE_Q && c == '\"')
		expand_and_add_to_output(ctx, shell, STA_NONE_Q, 3);
	else if (ctx->state == STA_SINGLE_Q && c == '\'')
		expand_and_add_to_output(ctx, shell, STA_NONE_Q, 4);
	else
		buf_add(&ctx->buf, c);
}

char	*expand_string(char *arg, t_shell *shell, t_expand *ctx)
{
	int		i;
	char	*tail;
	char	*expanded_tail;
	char	*old_out;

	buf_init(&ctx->buf);
	ctx->output = ft_strdup("");
	i = 0;
	while (arg[i])
		run_expand(arg[i++], shell, ctx);
	tail = buf_flush(&ctx->buf);
	if (ctx->state == STA_NONE_Q)
		expanded_tail = expand_all_type(tail, shell, ctx);
	else if (ctx->state == STA_DOUBLE_Q)
	{
		tail = remove_quote(tail);
		expanded_tail = expand_variables(tail, shell);
	}
	else
		expanded_tail = remove_quote(tail);
	old_out = ctx->output;
	ctx->output = ft_strjoin(old_out, expanded_tail);
	free(old_out);
	free(expanded_tail);
	return (ctx->output);
}

void	expand_command_args(t_command *cmd, t_shell *shell)
{
	t_expand	ctx;
	int			i;

	ctx.output = NULL;
	ctx.state = STA_NONE_Q;
	i = 1;
	if (cmd && cmd->argv[i])
	{
		while (cmd->argv && cmd->argv[i])
		{
			ctx.wild_flag = 0;
			ctx.expanded = expand_string(cmd->argv[i], shell, &ctx);
			free_buf(&ctx.buf);
			if (ctx.wild_flag)
			{
				generate_wildcard_matches(&ctx, cmd, &i);
				continue ;
			}
			cmd->argv[i] = ft_strdup(ctx.expanded);
			free(ctx.expanded);
			i++;
		}
	}
}

void	expander(t_andor *ast, t_shell *shell)
{
	t_list			*cmd_node;
	t_command		*cmd;

	if (!ast || ast->type != ANDOR_PIPELINE || !ast->pipeline
		|| !ast->pipeline->commands)
		return ;
	cmd_node = ast->pipeline->commands;
	while (cmd_node)
	{
		cmd = (t_command *)cmd_node->content;
		remove_quotes_from_redirs(cmd);
		if (cmd->argv && cmd->argv[0])
			expand_command_args(cmd, shell);
		if (cmd->subshell_ast)
			expand_andor_arguments(cmd->subshell_ast, shell);
		cmd_node = cmd_node->next;
	}
}

void	expand_andor_arguments(t_andor *ast, t_shell *shell)
{
	if (!ast)
		return ;
	if (ast->type == ANDOR_PIPELINE)
		expander(ast, shell);
	else if (ast->type == ANDOR_AND || ast->type == ANDOR_OR)
	{
		expand_andor_arguments(ast->left, shell);
		expand_andor_arguments(ast->right, shell);
	}
}
