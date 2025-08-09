/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shattori <shattori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 15:28:33 by nando             #+#    #+#             */
/*   Updated: 2025/08/09 12:58:03 by shattori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "builtin.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static int	is_numeric(const char *str)
{
	int	i;

	i = 0;
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	safe_exit_builtin(t_shell *shell, char **str, int status)
{
	int	i;

	free_env_list(shell->env);
	if (str)
	{
		i = 0;
		while (str[i])
		{
			free(str[i]);
			i++;
		}
		free(str);
	}
	rl_clear_history();
	exit(status);
}

int	builtin_exit(char **args, t_shell *shell)
{
	int	status;
	int	count;

	count = count_args(args);
	ft_printf("exit\n");
	if (!is_numeric(args[1]))
	{
		ft_fprintf(2, "minishell: exit: %s: numeric argument required\n",
			args[1]);
		safe_exit_builtin(shell, args, 2);
	}
	if (count > 2)
	{
		ft_fprintf(2, "minishell: exit: too many arguments\n");
		return (1);
	}
	else if (count == 1)
		safe_exit_builtin(shell, args, 0);
	status = ft_atoi(args[1]) % 256;
	if (status < 0)
		status += 256;
	safe_exit_builtin(shell, args, status);
	exit(-1);
}
