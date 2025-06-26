/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nando <nando@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 14:59:39 by nando             #+#    #+#             */
/*   Updated: 2025/06/26 15:02:12 by nando            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signal.h"

volatile sig_atomic_t	g_ack_status = 0;

static void	sigint_handler(int sig_number, siginfo_t *info, void *context)
{
	(void)sig_number;
	(void)info;
	(void)context;
	g_ack_status = 1;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	init_signal(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = sigint_handler;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

static void	prompt(void)
{
	char	*cmd;

	cmd = readline("minishell$ ");
	if (!cmd)
	{
		ft_printf("exit\n");
		exit(0);
	}
	add_history(cmd);
	free(cmd);
}

// int	main(void)
// {
// 	init_signal();
// 	while (1)
// 		prompt();
// 	exit(0);
// }
