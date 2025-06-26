/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nando <nando@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 15:40:45 by nando             #+#    #+#             */
/*   Updated: 2025/06/26 16:57:06 by nando            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

int	search_variable(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] && arg[i] != '$')
		i++;
	if (!arg[i])
		return (NOTHING);
	return (i);
}

void	create_env_key(char *arg, t_var *var, int i)
{
	var->start = i;
	var->len = 0;
	if (arg[i] == '?')
	{
		var->len = 1;
		var->key = ft_strdup("?");
		return ;
	}
	while (ft_isalnum(arg[i]) || arg[i] == '_')
	{
		var->len++;
		i++;
	}
	var->key = malloc(sizeof(char) * (var->len + 1));
	if (!var->key)
		return ;
	ft_strlcpy(var->key, &arg[var->start], var->len + 1);
}

void	search_env_value(t_var *var, t_env *env)
{
	int	g_exit_status;

	g_exit_status = 0;
	var->value = NULL;
	if (strcmp(var->key, "?") == 0)
	{
		var->value = ft_itoa(g_exit_status);
		return ;
	}
	while (env)
	{
		if (ft_strncmp(var->key, env->key, var->len + 1) == 0)
		{
			var->value = ft_strdup(env->value);
			break ;
		}
		env = env->next;
	}
}

char	*make_new_arg(char *arg, t_var *var)
{
	char	*prefix;
	char	*suffix;
	char	*tmp;
	char	*new_arg;

	prefix = ft_substr(arg, 0, var->start - 1);
	suffix = ft_strdup(&arg[var->start + var->len]);
	tmp = ft_strjoin(prefix, var->value);
	new_arg = ft_strjoin(tmp, suffix);
	free(prefix);
	free(suffix);
	free(tmp);
	free(var->value);
	return (new_arg);
}

char	*expand_variables(char *arg, t_env *env_head)
{
	int		i;
	t_var	*var;
	char	*new_arg;

	var = init_var();
	if (!var)
		return (NULL);
	while (1)
	{
		i = search_variable(arg);
		if (i == NOTHING)
			break ;
		i++;
		create_env_key(arg, var, i);
		search_env_value(var, env_head);
		if (!var->value)
			var->value = ft_strdup("");
		new_arg = make_new_arg(arg, var);
		free(var->key);
		free(arg);
		arg = new_arg;
	}
	free(var);
	return (arg);
}
