/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_searchpath.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nando <nando@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 10:21:49 by shattori          #+#    #+#             */
/*   Updated: 2025/07/31 20:09:57 by nando            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static char	*get_path_variable(t_env *env)
{
	return (get_env_value("PATH", env));
}

static char	**split_path_variable(char *path_var)
{
	if (!path_var)
		return (NULL);
	return (ft_split(path_var, ":"));
}

static char	*get_valid_executable_path(char **paths, char *cmd)
{
	char	*full_path;
	int		i;

	i = 0;
	while (paths[i])
	{
		full_path = ft_strjoin_path(paths[i], cmd);
		if (!full_path)
			return (NULL);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

char	*search_path(char *cmd, t_env *env)
{
	char	*path_var;
	char	**paths;
	char	*full_path;

	if (!cmd)
		exit(0);
	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	path_var = get_path_variable(env);
	if (!path_var)
		return (NULL);
	paths = split_path_variable(path_var);
	if (!paths)
		return (NULL);
	full_path = get_valid_executable_path(paths, cmd);
	free_split(paths);
	return (full_path);
}
