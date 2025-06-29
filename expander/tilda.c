/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilda.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nando <nando@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 15:40:14 by nando             #+#    #+#             */
/*   Updated: 2025/06/26 17:00:53 by nando            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

char	*get_home_value(t_env *env)
{
	while (env)
	{
		if (strcmp(env->key, "HOME") == 0)
			return (ft_strdup(env->value));
		env = env->next;
	}
	return (NULL);
}

char	*expand_tilda(char *arg, t_env *env)
{
	char	*home;
	char	*joined;

	if (arg[0] != '~')
		return (ft_strdup(arg));
	home = get_home_value(env);
	if (!home)
		return (ft_strdup(arg));
	if (arg[1] == '\0')
		return (home);
	if (arg[1] == '/')
	{
		joined = ft_strjoin(home, &arg[1]);
		free(home);
		return (joined);
	}
	free(home);
	return (ft_strdup(arg));
}
