/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nando <nando@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 01:08:04 by nando             #+#    #+#             */
/*   Updated: 2025/08/01 15:48:12 by nando            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*   Updated: 2025/07/25 09:15:49 by shattori         ###   ########.fr       */
/*   Updated: 2025/07/28 12:16:19 by shattori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	add_history_and_parse(t_token *lex, t_shell *shell, char *cmd, t_ast **ast)
{
	has_syntax_error(lex, shell);
	if (shell->exit_status == 258)
		add_history(cmd);
	if (shell->exit_status == 258)
	{
		free_tokens(lex);
		shell->exit_status = 2;
		return (-1);
	}
	*ast = start_parse(lex);
	free_tokens(lex);
	if (!*ast)
		return (-1);
	add_history(cmd);
	return (1);
}

t_andor	*make_linearized_ast(char *cmd, t_shell *shell, t_ast **ast)
{
	t_token	*lex;
	t_andor	*linearized_ast;

	lex = lexer(cmd);
	if (!lex)
		return (NULL);
	if (!add_history_and_parse(lex, shell, cmd, ast))
		return (NULL);
	linearized_ast = linearizer(*ast, shell);
	if (g_ack_status)
	{
		free_andor_ast(linearized_ast);
		return (NULL);
	}
	if (!linearized_ast)
		return (NULL);
	if (g_ack_status)
		return (NULL);
	return (linearized_ast);
}

void	expand_and_execute(t_andor *linearized_ast, t_shell *shell)
{
	expand_andor_arguments(linearized_ast, shell);
	executor(linearized_ast, shell);
}

int	prompt(t_shell *shell)
{
	char	*cmd;
	t_andor	*linearized_ast;
	t_ast	*ast;

	ast = NULL;
	cmd = run_readline(shell);
	if (!cmd || cmd[0] == '\0')
	{
		if (cmd)
			free(cmd);
		return (0);
	}
	linearized_ast = make_linearized_ast(cmd, shell, &ast);
	if (!linearized_ast)
	{
		// printf("linearized ast is NULL\n");
		if (cmd)
			free(cmd);
		return (0);
	}
	expand_and_execute(linearized_ast, shell);
	free_ast(ast);
	free_andor_ast(linearized_ast);
	free(cmd);
	return (1);
}

int	main(int ac, char **av, char **envp)
{
	t_shell	shell;

	(void)ac;
	(void)av;
	shell.is_interactive = isatty(STDIN_FILENO);
	init_signal();
	shell.env = init_env(envp);
	shell.exit_status = 0;
	while (1)
	{
		if (!prompt(&shell))
			continue ;
	}
	rl_clear_history();
	free_env_list(shell.env);
	return (0);
}
