/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shattori <shattori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:27:05 by shattori          #+#    #+#             */
/*   Updated: 2025/07/04 17:27:06 by shattori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

char	**convert_env(t_env *env)
{
	char	**envp;
	t_env	*cur;
	int		i;
	int		size;

	size = env_size(env);
	envp = malloc(sizeof(char *) * (size + 1));
	if (!envp)
		return (NULL);
	i = 0;
	cur = env;
	while (cur)
	{
		envp[i] = ft_strjoin_3(cur->key, "=", cur->value);
		i++;
		cur = cur->next;
	}
	envp[i] = NULL;
	return (envp);
}

char	*get_env_value(const char *name, t_env *env)
{
	while (env)
	{
		if (ft_strcmp(env->key, name) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

int	env_size(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

char	*ft_strjoin_3(char *s1, char *s2, char *s3)
{
	char	*tmp;
	char	*res;

	tmp = ft_strjoin(s1, s2);
	res = ft_strjoin(tmp, s3);
	free(tmp);
	return (res);
}

char	*ft_strjoin_path(char *dir, char *file)
{
	char	*tmp;
	char	*res;

	tmp = ft_strjoin(dir, "/");
	res = ft_strjoin(tmp, file);
	free(tmp);
	return (res);
}
