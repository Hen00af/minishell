/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nando <nando@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 19:30:38 by nando             #+#    #+#             */
/*   Updated: 2025/07/10 19:31:33 by nando            ###   ########.fr       */
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
	size_t	i;

	i = 0;
	while (string1[i] && string2[i])
	{
		if ((int)((string1[i] != string2[i])))
			return ((unsigned char)string1[i] - (unsigned char)string2[i]);
		i++;
	}
	return ((unsigned char)string1[i] - (unsigned char)string2[i]);
}

void	delete_list_head(t_env **env)
{
	t_env	*tmp;

	tmp = *env;
	*env = (*env)->next;
	free(tmp->key);
	free(tmp->value);
	free(tmp);
}

int	delete_env_node(t_env *prev, const char *target_key)
{
	t_env	*current;

	current = prev->next;
	if (ft_strcmp(target_key, current->key) == 0)
	{
		prev->next = current->next;
		free(current->key);
		free(current->value);
		free(current);
		return (1);
	}
	return (0);
}
