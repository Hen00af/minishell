/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nando <nando@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 15:28:29 by nando             #+#    #+#             */
/*   Updated: 2025/07/07 21:16:11 by nando            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	is_valid_initial(char c)
{
	if (c == '_')
		return (OK);
	else if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (OK);
	return (NG);
}

int	ft_strcmp(const char *string1, const char *string2)
{
	size_t	s;

	s = 0;
	while (string1[s] && string2[s])
	{
		if ((int)((string1[s] != string2[s])))
			return ((unsigned char)string1[s] - (unsigned char)string2[s]);
		s++;
	}
	return ((unsigned char)string1[s] - (unsigned char)string2[s]);
}

void	delete_list_head(t_env **list_head)
{
	t_env	*tmp;

	tmp = *list_head;
	*list_head = (*list_head)->next;
	free(tmp->key);
	free(tmp->value);
	free(tmp);
}

void	delete_env_node(t_env *prev, const char *target_key)
{
	t_env	*current;

	current = prev->next;
	while (current)
	{
		if (ft_strcmp(target_key, current->key) == 0)
		{
			prev->next = current->next;
			free(current->key);
			free(current->value);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
	return ;
}

int	builtin_unset(char **args, t_env **list_head)
{
	int		i;
	t_env	*prev;
	int		status;

	i = 1;
	status = 0;
	if (!*list_head)
		return (0);
	while (args[i])
	{
		if (is_valid_initial(args[i][0]) == 1)
		{
			status = 1;
			i++;
			continue ;
		}
		if (ft_strcmp(args[i], (*list_head)->key) == 0)
		{
			delete_list_head(list_head);
			i++;
			continue ;
		}
		prev = *list_head;
		delete_env_node(prev, args[i]);
		i++;
	}
	if (status == 1)
		return (NG);
	return (OK);
}
