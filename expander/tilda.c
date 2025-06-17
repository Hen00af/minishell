/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilda.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nando <nando@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 15:40:14 by nando             #+#    #+#             */
/*   Updated: 2025/06/17 14:37:17 by nando            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

char	*expand_tilda(char *arg, t_env *env)
{
	char *home_value;
	char *joined;

	home_value = NULL;
	if (arg[0] != '~')
		return (ft_strdup(arg));

	while (env)
	{
		if (strcmp(env->key, "HOME") == 0)
		{
			home_value = ft_strdup(env->value);
			break ;
		}
		env = env->next;
	}
	if (!home_value)
		return (ft_strdup(arg));

	if (arg[1] == '\0')
		return (home_value);

	if (arg[1] == '/')
	{
		joined = ft_strjoin(home_value, &arg[1]);
		free(home_value);
		return (joined);
	}
	free(home_value);
	return (ft_strdup(arg));
}
