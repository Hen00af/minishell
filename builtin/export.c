/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shattori <shattori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 15:30:31 by nando             #+#    #+#             */
/*   Updated: 2025/06/21 16:50:19 by shattori         ###   ########.fr       */
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

	env_array = env_to_array(list_head);
	sort_array(env_array);
	print_env_array(env_array);
}

int	is_valid_initial(char c)
{
	if (c == '_')
		return (0);
	else if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (0);
	return (1);
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
	int	i;
	int	status;

	i = 1;
	status = 0;
	if (args[i] == NULL)
		sort_and_print_environ(*list_head);
	while (args[i])
	{
		if (is_valid_initial(args[i][0]) == 1)
		{
			status = 1;
			i++;
			continue ;
		}
		check_and_register_env(args[i], *list_head);
		i++;
	}
	if (status == 1)
		return (NG);
	return (OK);
}

// int main(void)
// {
//     char *env[] = {
//         "PATH=/usr/bin",
//         "HOME=/home/user",
//         "LANG=en_US.UTF-8",
//         "SHELL=/bin/bash",
//         NULL
//     };

//     printf("=== Before Sort ===\n");
//     print_env_array(env);

//     sort_array(env);

//     printf("=== After Sort ===\n");
//     print_env_array(env);

//     return (0);
// }
