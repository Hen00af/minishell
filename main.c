/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shattori <shattori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 01:08:04 by nando             #+#    #+#             */
/*   Updated: 2025/07/28 13:15:19 by shattori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*   Updated: 2025/07/25 09:15:49 by shattori         ###   ########.fr       */
/*   Updated: 2025/07/28 12:16:19 by shattori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

t_andor	*make_linearized_ast(char *cmd, t_shell *shell, t_ast **ast)
{
	t_token	*lex;
	t_andor	*linearized_ast;

	lex = lexer(cmd);
	if (!lex)
		return (NULL);
	shell->exit_status = has_syntax_error(lex);
	if (shell->exit_status)
	{
		free_tokens(lex);
		return (NULL);
	}
	*ast = start_parse(lex);
	free_tokens(lex);
	if (!*ast)
		return (NULL);
	add_history(cmd);
	linearized_ast = linearizer(*ast, shell);
	if (!linearized_ast)
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
	if (!cmd)
		return (0);
	linearized_ast = make_linearized_ast(cmd, shell, &ast);
	if (!linearized_ast)
	{
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
