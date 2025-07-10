/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nando <nando@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 15:28:29 by nando             #+#    #+#             */
/*   Updated: 2025/07/10 19:39:29 by nando            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	process_unset_arg(char *arg, t_env **env, int *status)
{
	t_env	*prev;

	if (!*env)
		return (OK);
	if (is_valid_initial(arg[0]) == NG)
		return (NG);
	if (ft_strcmp(arg, (*env)->key) == OK)
	{
		delete_list_head(env);
		return (OK);
	}
	prev = *env;
	while (prev && prev->next)
	{
		if (delete_env_node(prev, arg))
			return (OK);
		prev = prev->next;
	}
	return (OK);
}

int	builtin_unset(char **args, t_env **env)
{
	int		i;
	t_env	*prev;
	int		status;

	i = 1;
	status = OK;
	if (!*env)
		return (status);
	while (args[i])
	{
		if (process_unset_arg(args[i], env, &status) == NG)
			status = NG;
		i++;
	}
	return (status);
}
