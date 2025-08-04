/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linearizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shattori <shattori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 16:14:37 by shattori          #+#    #+#             */
/*   Updated: 2025/08/04 14:36:59 by shattori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./linearizer.h"

char	**copy_argv(char **argv)
{
	char	**copy;
	int		i;
	int		count;

	if (!argv)
		return (NULL);
	count = 0;
	while (argv[count])
		count++;
	copy = ft_calloc(count + 1, sizeof(char *));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < count)
	{
		copy[i] = ft_strdup(argv[i]);
		if (!copy[i])
		{
			while (--i >= 0)
				free(copy[i]);
			free(copy);
			return (NULL);
		}
		i++;
	}
	return (copy);
}

int	add_redirection(t_command *cmd, t_ast *ast)
{
	t_redirection	*redir;
	t_list			*redir_node;

	redir = ft_calloc(1, sizeof(t_redirection));
	if (!redir)
		return (0);
	redir->type = map_redir_type(ast->type);
	if (ast->filename)
	{
		redir->filename = ft_strdup(ast->filename);
		if (!redir->filename)
		{
			free(redir);
			return (0);
		}
	}
	else
		redir->filename = NULL;
	redir_node = ft_lstnew(redir);
	if (!redir_node)
	{
		if (redir->filename)
			free(redir->filename);
		free(redir);
		return (0);
	}
	ft_lstadd_back(&cmd->redirections, redir_node);
	return (1);
}
