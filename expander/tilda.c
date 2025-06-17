/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilda.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nando <nando@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 15:40:14 by nando             #+#    #+#             */
/*   Updated: 2025/06/17 09:32:52 by nando            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

char	*expand_tilda(char *arg, t_env *env)
{
	char	*replace_arg;
	char	*tmp;

	replace_arg = NULL;
	if (arg[0] != '~')
		return (arg);
	while (env)
	{
		if (strcmp(env->key, "HOME") == 0)
		{
			replace_arg = ft_strdup(env->value);
			break ;
		}
		env = env->next;
	}
	if (!replace_arg)
		return (arg);
	if (arg[1] == '\0')
		return (replace_arg);
	if (arg[1] == '/')
	{
		tmp = replace_arg;
		replace_arg = ft_strjoin(replace_arg, &arg[1]);
		free(tmp);
		return (replace_arg);
	}
	else
	{
		free(replace_arg);
		return (arg);
	}
}
