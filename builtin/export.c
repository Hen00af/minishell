/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nando <nando@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 15:30:31 by nando             #+#    #+#             */
/*   Updated: 2025/07/07 21:20:28 by nando            ###   ########.fr       */
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

void	print_env_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		printf("declare -x %s\n", array[i]);
		i++;
	}
}

void	sort_and_print_environ(t_env *list_head)
{
	char	**env_array;
	int		i;

	i = 0;
	env_array = env_to_array(list_head);
	sort_array(env_array);
	print_env_array(env_array);
	while (env_array[i])
	{
		free(env_array[i]);
		i++;
	}
	free(env_array);
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

void	include_only_key(char *key, t_env *current)
{
	while (current)
	{
		if ((ft_strcmp(key, current->key) == 0))
		{
			if (current->flag == 0)
				current->flag = 1;
			return ;
		}
		else if (current->next == NULL)
		{
			current->next = create_env_node_only_key(key);
			return ;
		}
		current = current->next;
	}
}

void	include_key_value(char *env, t_env *current)
{
	char	**key_value;

	key_value = env_split(env, '=');
	while (current)
	{
		if ((ft_strcmp(key_value[0], current->key)) == 0)
		{
			if (current->flag == 0)
				current->flag = 1;
			free(current->value);
			current->value = ft_strdup(key_value[1]);
			free_key_value(key_value);
			return ;
		}
		else if (current->next == NULL)
		{
			current->next = create_env_node(key_value);
			free_key_value(key_value);
			return ;
		}
		current = current->next;
	}
}

void	check_and_register_env(char *env, t_env *current)
{
	int	i;
	int	equal_flag;

	i = 0;
	equal_flag = 0;
	while (env[i])
	{
		if (env[i] == '=')
			equal_flag = 1;
		i++;
	}
	if (equal_flag == 0)
	{
		include_only_key(env, current);
		return ;
	}
	else
	{
		include_key_value(env, current);
		return ;
	}
}
int	builtin_export(char **args, t_env **list_head)
{
	int		i;
	int		status;
	char	*key;
	char	*keybuf;
	size_t	len;

	i = 1;
	status = OK;
	if (args[i] == NULL)
	{
		sort_and_print_environ(*list_head);
		return (status);
	}
	while (args[i])
	{
		key = ft_strchr(args[i], '=');
		if (key)
			len = (key - args[i]);
		else
			len = ft_strlen(args[i]);
		keybuf = malloc(sizeof(char) * (len + 1));
		ft_strlcpy(keybuf, args[i], len + 1);
		if (is_valid_key(keybuf) == NG)
		{
			ft_putstr_fd("export: `", 2);
			ft_putstr_fd(args[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			status = NG;
		}
		else
			check_and_register_env(args[i], *list_head);
		free(keybuf);
		i++;
	}
	return (status);
}
