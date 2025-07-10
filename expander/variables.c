/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nando <nando@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 15:40:45 by nando             #+#    #+#             */
/*   Updated: 2025/07/10 23:43:55 by nando            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

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

void	search_env_value(t_var *var, t_shell *shell)
{
	t_env	*env;

	env = shell->env;
	var->value = NULL;
	if (strcmp(var->key, "?") == 0)
	{
		var->value = ft_itoa(shell->exit_status);
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

static char	*expand_variable_loop(char *arg, t_shell *shell, t_var *var)
{
	int		i;
	int		start;
	char	*new_arg;

	start = 0;
	while (1)
	{
		i = search_variable(arg, start);
		if (arg[i + 1] == '\0' || i == NOTHING)
			break ;
		if (!ft_isalpha(arg[i + 1]) && arg[i + 1] != '_' && arg[i + 1] != '?')
		{
			start = i + 1;
			continue ;
		}
		i++;
		get_value(arg, var, shell, i);
		if (!var->value)
			var->value = ft_strdup("");
		new_arg = make_new_arg(arg, var);
		free(var->key);
		free(arg);
		arg = new_arg;
	}
	return (arg);
}

char	*expand_variables(char *arg, t_shell *shell)
{
	t_var	*var;
	char	*result;

	var = init_var();
	if (!var)
		return (NULL);
	result = expand_variable_loop(arg, shell, var);
	free(var);
	return (result);
}
