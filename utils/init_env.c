/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nando <nando@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 15:05:25 by nando             #+#    #+#             */
/*   Updated: 2025/07/05 02:47:31 by nando            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>
#include <stdlib.h>

char	**env_split(char const *s, char c)
{
	char	**result;

	if (!s)
		return (NULL);
	result = malloc(3 * sizeof(char *));
	if (!result)
		return (NULL);
	result = create_split(s, result, c);
	return (result);
}

t_env	*create_env_node(char **key_value)
{
	t_env	*env_node;

	env_node = malloc(sizeof(t_env));
	if (!env_node)
		return (NULL);
	env_node->key = ft_strdup(key_value[0]);
	if (!env_node->key)
		return (NULL);
	env_node->value = ft_strdup(key_value[1]);
	if (!env_node->value)
	{
		free(env_node->key);
		free(env_node);
		return (NULL);
	}
	env_node->flag = 1;
	env_node->next = NULL;
	return (env_node);
}

bool	append_env_node(t_env **head, t_env **tail, char **key_value)
{
	t_env	*node;

	node = create_env_node(key_value);
	if (!node)
		return (false);
	if (!*head)
		*head = node;
	else
		(*tail)->next = node;
	*tail = node;
	return (true);
}

t_env	*init_env(char **envp)
{
	t_env	*head;
	t_env	*tail;
	char	**kv;
	int		i;

	head = NULL;
	tail = NULL;
	i = 0;
	while (envp[i])
	{
		kv = env_split(envp[i++], '=');
		if (!kv)
			return (NULL);
		if (!kv[1])
			kv[1] = ft_strdup("");
		if (!append_env_node(&head, &tail, kv))
			return (NULL);
		free(kv[0]);
		free(kv[1]);
		free(kv);
	}
	return (head);
}
