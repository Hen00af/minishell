/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nando <nando@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 15:02:10 by nando             #+#    #+#             */
/*   Updated: 2025/07/10 19:24:25 by nando            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "builtin.h"

int	set_pwd(t_env *list_head, char *pwd, int len)
{
	char	cwd[1000];
	char	*key_value[2];

	if (!getcwd(cwd, 1000))
	{
		perror("getcwd");
		return (NG);
	}
	set_key_value(key_value, pwd, cwd);
	while (list_head)
	{
		if (ft_strncmp(list_head->key, pwd, len) == 0)
			return (update_pwd_value(list_head, cwd));
		else if (list_head->next == NULL)
			return (create_pwd_node(list_head, key_value));
		list_head = list_head->next;
	}
	return (OK);
}

char	*resolve_cd_path(char *arg)
{
	char	*home;

	if (!arg)
	{
		home = getenv("HOME");
		if (!home)
		{
			fprintf(stderr, "minishell: cd: HOME not set\n");
			return (NULL);
		}
		return (ft_strdup(home));
	}
	else
		return (ft_strdup(arg));
}

int	perform_cd(char *path, t_env *env)
{
	struct stat	dir_stat;

	if (stat(path, &dir_stat) == -1)
	{
		fprintf(stderr, " No such file or directory\n");
		return (NG);
	}
	if (!S_ISDIR(dir_stat.st_mode))
	{
		fprintf(stderr, " Not a directory\n");
		return (NG);
	}
	if (set_pwd(env, "OLDPWD", 6) == NG)
		return (NG);
	if (chdir(path) == -1)
	{
		fprintf(stderr, " chdir error\n");
		return (NG);
	}
	if (set_pwd(env, "PWD", 3) == NG)
		return (NG);
	return (OK);
}

int	builtin_cd(char **args, t_env *env)
{
	char	*path;
	int		status;

	if (check_cd_args(args) == NG)
		return (NG);
	path = resolve_cd_path(args[1]);
	if (!path)
		return (NG);
	status = perform_cd(path, env);
	free(path);
	return (status);
}
