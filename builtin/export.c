/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nando <nando@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 15:30:31 by nando             #+#    #+#             */
/*   Updated: 2025/07/24 19:24:44 by nando            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

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
		include_only_key(env, current);
	else
		include_key_value(env, current);
	return ;
}

void	process_export_arg(char **args, int i, t_env **env, int *status)
{
	char	*key;
	size_t	len;
	char	*keybuf;

	key = ft_strchr(args[i], '=');
	if (key)
		len = (key - args[i]);
	else
		len = ft_strlen(args[i]);
	keybuf = malloc(sizeof(char) * (len + 1));
	ft_strlcpy(keybuf, args[i], len + 1);
	if (is_valid_key(keybuf) == NG)
	{
		ft_putstr_fd("export: '", 2);
		ft_putstr_fd(args[i], 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		*status = NG;
	}
	else
		check_and_register_env(args[i], *env);
	free(keybuf);
}

int	builtin_export(char **args, t_env **env)
{
	int	i;
	int	status;

	i = 1;
	status = OK;
	if (args[i] == NULL)
		return (sort_and_print_environ(*env));
	while (args[i])
	{
		process_export_arg(args, i, env, &status);
		i++;
	}
	return (status);
}
