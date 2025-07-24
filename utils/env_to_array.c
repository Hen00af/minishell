/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nando <nando@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 15:57:37 by nando             #+#    #+#             */
/*   Updated: 2025/07/24 19:34:40 by nando            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "utils.h"

void	free_environ(char **environ, int i)
{
	i--;
	while (i >= 0)
	{
		free(environ[i]);
		i--;
	}
	free(environ);
	return ;
}

int	count_env_list(t_env *list_head)
{
	int	i;

	i = 0;
	while (list_head)
	{
		if (list_head->flag == 1)
			i++;
		list_head = list_head->next;
	}
	return (i);
}

int	create_env_array(char **environ, t_env *list_head)
{
	char	*key_value;
	char	*tmp;
	int		i;

	i = 0;
	while (list_head)
	{
		if (list_head->flag == 1)
		{
			tmp = ft_strjoin(list_head->key, "=");
			key_value = create_key_value(list_head, tmp);
			free(tmp);
			environ[i] = ft_strdup(key_value);
			if (!environ[i])
			{
				free_environ(environ, i);
				return (ERROR);
			}
			free(key_value);
		}
		list_head = list_head->next;
		i++;
	}
	return (0);
}

char	**env_to_array(t_env *list_head)
{
	t_env	*env_tmp;
	char	**environ;
	int		i;

	env_tmp = list_head;
	i = count_env_list(list_head);
	environ = malloc(sizeof(char *) * (i + 1));
	if (!environ)
		return (NULL);
	list_head = env_tmp;
	if (create_env_array(environ, list_head) == ERROR)
		return (NULL);
	environ[i] = NULL;
	return (environ);
}

t_env	*create_test_env(char *key, char *value)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = key;
	node->value = value;
	node->flag = 1;
	node->next = NULL;
	return (node);
}
