/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shattori <shattori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 21:31:05 by nando             #+#    #+#             */
/*   Updated: 2025/07/25 09:23:34 by shattori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	free_env_list(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		if (env->key)
			free(env->key);
		if (env->value)
			free(env->value);
		if (env)
			free(env);
		env = tmp;
	}
}

void	free_inserted_memory(char **result, int j)
{
	j = j - 1;
	while (j >= 0)
	{
		free(result[j]);
		j--;
	}
	free(result);
}

char	*create_key(char const *s, char c)
{
	char	*new_string;
	int		len;
	int		i;

	len = 0;
	i = 0;
	while (s[len] && s[len] != c)
		len++;
	new_string = malloc((len + 1) * sizeof(char));
	if (!new_string)
		return (NULL);
	while (i < len)
	{
		new_string[i] = s[i];
		i++;
	}
	new_string[i] = '\0';
	return (new_string);
}

char	*create_value(char const *s)
{
	char	*new_string;
	int		len;
	int		i;

	len = 0;
	i = 0;
	while (s[len])
		len++;
	new_string = malloc((len + 1) * sizeof(char));
	if (!new_string)
		return (NULL);
	while (i < len)
	{
		new_string[i] = s[i];
		i++;
	}
	new_string[i] = '\0';
	return (new_string);
}

char	**create_split(char const *s, char **result, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	result[j] = create_key(&s[i], c);
	if (!result[j])
	{
		free_inserted_memory(result, j);
		return (NULL);
	}
	while (s[i] != '=')
		i++;
	i++;
	result[++j] = create_value(&s[i]);
	result[++j] = NULL;
	return (result);
}
