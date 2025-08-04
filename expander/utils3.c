/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nando <nando@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 17:12:10 by nando             #+#    #+#             */
/*   Updated: 2025/08/04 17:55:03 by nando            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

t_file_node	*create_new_node(char *file_name)
{
	t_file_node	*new_node;

	new_node = malloc(sizeof(t_file_node));
	if (!new_node)
		return (NULL);
	new_node->name = ft_strdup(file_name);
	if (!new_node->name)
	{
		free(new_node);
		return (NULL);
	}
	new_node->next = NULL;
	return (new_node);
}

bool	append_file_node(t_file_node **head, t_file_node **tail, char *name)
{
	t_file_node	*node;

	node = create_new_node(name);
	if (!node)
		return (false);
	if (!*head)
		*head = node;
	else
		(*tail)->next = node;
	*tail = node;
	return (true);
}

void	create_new_args(t_expand *ctx, t_command *cmd, int i)
{
	int	j;
	int	k;
	int	l;

	j = 0;
	k = 0;
	while (j < i)
	{
		ctx->new_argv[j] = ft_strdup(cmd->argv[j]);
		j++;
	}
	while (k < ctx->count_sw)
	{
		ctx->new_argv[j + k] = ft_strdup(ctx->split_words[k]);
		k++;
	}
	ctx->expand_point = j + k;
	l = i + 1;
	while (cmd->argv[l])
	{
		ctx->new_argv[j + k] = ft_strdup(cmd->argv[l]);
		k++;
		l++;
	}
	ctx->new_argv[j + k] = NULL;
}

void	generate_wildcard_matches(t_expand *ctx, t_command *cmd, int *i)
{
	ctx->split_words = ft_split(ctx->expanded, " ");
	ctx->count_av = count_args(cmd->argv);
	ctx->count_sw = count_args(ctx->split_words);
	ctx->new_argv = malloc(sizeof(char *) * ((ctx->count_av + ctx->count_sw)
				+ 1));
	create_new_args(ctx, cmd, *i);
	*i = ctx->expand_point;
	cmd->argv = ctx->new_argv;
	free_args(ctx->split_words);
	free(ctx->expanded);
	return ;
}

int	process_entries(DIR *dir, t_file_node **head, t_file_node **tail)
{
	struct dirent	*entry;

	entry = readdir(dir);
	while (entry)
	{
		if (entry->d_name[0] != '.')
		{
			if (!append_file_node(head, tail, entry->d_name))
				return (0);
		}
		entry = readdir(dir);
	}
	return (1);
}
