/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shattori <shattori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 01:08:04 by nando             #+#    #+#             */
/*   Updated: 2025/07/25 04:13:50 by shattori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

char	*run_readline(t_shell *shell)
{
	char	*cwd;
	char	*prompt;
	char	*cmd;

	cwd = NULL;
	prompt = NULL;
	cmd = NULL;
	if (shell->is_interactive)
	{
		cwd = getcwd(NULL, 0);
		if (!cwd)
			return (NULL);
		prompt = ft_strjoin(cwd, " $ ");
		free(cwd);
		cmd = readline(prompt);
		free(prompt);
	}
	else
		cmd = get_next_line(STDIN_FILENO);
	if (!cmd)
	{
		if (shell->is_interactive)
			ft_putstr_fd("exit\n", STDOUT_FILENO);
		exit(shell->exit_status);
	}
	if (g_ack_status == 1)
	{
		g_ack_status = 0;
		shell->exit_status = 130;
		free(cmd);
		return (ft_strdup(""));
	}
	return (cmd);
}

t_andor	*make_linearized_ast(char *cmd, t_shell *shell)
{
	t_token	*lex;
	t_ast	*ast;
	t_andor	*linearized_ast;

	lex = lexer(cmd);
	if (!lex)
		return (NULL);
	ast = start_parse(lex);
	free_tokens(lex);
	if (!ast)
		return (NULL);
	add_history(cmd);
	linearized_ast = linearizer(ast, shell);
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

	cmd = run_readline(shell);
	if (!cmd)
		return (0);
	linearized_ast = make_linearized_ast(cmd, shell);
	if (!linearized_ast)
	{
		free(cmd);
		return (0);
	}
	expand_and_execute(linearized_ast, shell);
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
	free_env_list(shell.env);
	return (0);
}
