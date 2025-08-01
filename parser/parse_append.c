/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_append.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shattori <shattori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 17:23:44 by shattori          #+#    #+#             */
/*   Updated: 2025/07/25 10:00:22 by shattori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static char	**copy_argv(char **argv, int argc)
{
	char	**new_argv;
	int		i;

	new_argv = ft_calloc(argc + 2, sizeof(char *));
	if (!new_argv)
		return (NULL);
	i = 0;
	while (i < argc)
	{
		new_argv[i] = ft_strdup(argv[i]);
		i++;
	}
	return (new_argv);
}

void	free_argv(char **argv)
{
	int	i;

	if (!argv)
		return ;
	i = 0;
	while (argv[i])
		free(argv[i++]);
	free(argv);
}

int	append_argv(t_ast *cmd, char *word)
{
	int		argc;
	char	**new_argv;

	if (!word)
		return (1);
	argc = 0;
	while (cmd->argv && cmd->argv[argc])
		argc++;
	new_argv = copy_argv(cmd->argv, argc);
	if (!new_argv)
		return (1);
	new_argv[argc] = ft_strdup(word);
	if (!new_argv[argc])
	{
		free_argv(new_argv);
		return (1);
	}
	new_argv[argc + 1] = NULL;
	free_argv(cmd->argv);
	cmd->argv = new_argv;
	cmd->type = NODE_COMMAND;
	return (0);
}
