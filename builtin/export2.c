/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nando <nando@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 19:28:36 by nando             #+#    #+#             */
/*   Updated: 2025/07/24 19:24:35 by nando            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	free_key_value(char **key_value)
{
	free(key_value[0]);
	free(key_value[1]);
	free(key_value);
}

void	sort_array(char **array)
{
	int		size;
	int		i;
	int		j;
	char	*tmp;

	size = 0;
	i = 0;
	while (array[size])
		size++;
	while (i < size - 1)
	{
		j = 0;
		while (j < size - i - 1)
		{
			if (ft_strcmp(array[j], array[j + 1]) > 0)
			{
				tmp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

int	sort_and_print_environ(t_env *env)
{
	char	**env_array;
	int		i;

	i = 0;
	env_array = env_to_array(env);
	sort_array(env_array);
	while (env_array[i])
	{
		printf("declare -x %s\n", env_array[i]);
		i++;
	}
	i = 0;
	while (env_array[i])
	{
		free(env_array[i]);
		i++;
	}
	free(env_array);
	return (OK);
}

int	is_valid_key(char *key)
{
	int	i;

	if (!key || !(ft_isalpha(key[0]) || key[0] == '_'))
		return (NG);
	i = 1;
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (NG);
		i++;
	}
	return (OK);
}

t_env	*create_env_node_only_key(char *key)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->key = ft_strdup(key);
	if (!new_node->key)
		return (NULL);
	new_node->value = NULL;
	new_node->flag = 1;
	new_node->next = NULL;
	return (new_node);
}
