/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_readline.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nando <nando@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 05:32:41 by shattori          #+#    #+#             */
/*   Updated: 2025/07/31 17:56:04 by nando            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static char	*get_input_line(t_shell *shell)
{
	char	*cwd;
	char	*prompt;
	char	*cmd;

	if (shell->is_interactive)
	{
		cwd = getcwd(NULL, 0);
		if (!cwd)
			return (NULL);
		prompt = ft_strjoin(cwd, " $ ");
		free(cwd);
		if (!prompt)
			return (NULL);
		cmd = readline(prompt);
		free(prompt);
		return (cmd);
	}
	else
	{
		cmd = get_next_line(STDIN_FILENO);
		return (cmd);
	}
}

char	*run_readline(t_shell *shell)
{
	char	*cmd;

	cmd = get_input_line(shell);
	if (g_ack_status == 1)
	{
		g_ack_status = 0;
		shell->exit_status = 130;
	}
	if (!cmd)
	{
		if (shell->is_interactive)
			ft_putstr_fd("exit\n", STDOUT_FILENO);
		exit(shell->exit_status);
	}
	return (cmd);
}
