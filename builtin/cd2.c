/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nando <nando@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 19:23:37 by nando             #+#    #+#             */
/*   Updated: 2025/07/10 19:24:36 by nando            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	set_key_value(char **key_value, char *pwd, char *cwd)
{
	key_value[0] = pwd;
	key_value[1] = cwd;
}

int	update_pwd_value(t_env *node, const char *cwd)
{
	free(node->value);
	node->value = ft_strdup(cwd);
	if (node->value)
		return (OK);
	return (NG);
}

int	create_pwd_node(t_env *node, char **key_value)
{
	node->next = create_env_node(key_value);
	if (node->next)
		return (OK);
	return (NG);
}

int	check_cd_args(char **args)
{
	if (args[1] && args[2])
	{
		fprintf(stderr, " too many arguments\n");
		return (NG);
	}
	return (OK);
}
