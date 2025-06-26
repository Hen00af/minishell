/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nando <nando@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 20:23:19 by nando             #+#    #+#             */
/*   Updated: 2025/06/26 20:46:06 by nando            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

bool	has_wildcard(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '*')
			return (true);
		i++;
	}
	return (false);
}

bool	is_match(const char *pattern, const char *str, int i, int j)
{
	if (pattern[i] == '\0' && str[j] == '\0')
		return (true);
	if (pattern[i] == '*')
	{
		return (is_match(pattern, str, i + 1, j) || (str[j] && is_match(pattern,
					str, i, j + 1)));
	}
	if (pattern[i] == str[j])
		return (is_match(pattern, str, i + 1, j + 1));
	return (false);
}

void	swap_name(t_file_node *current, t_file_node *next)
{
	char	*tmp;

	tmp = current->name;
	current->name = next->name;
	next->name = tmp;
}

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
