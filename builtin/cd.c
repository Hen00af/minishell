/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nando <nando@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 15:02:10 by nando             #+#    #+#             */
/*   Updated: 2025/07/09 10:48:27 by nando            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "builtin.h"
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

void	set_key_value(char **key_value, char *pwd, char *cwd)
{
	key_value[0] = pwd;
	key_value[1] = cwd;
}

int	set_pwd(t_env *list_head, char *pwd, int num)
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
		if (ft_strncmp(list_head->key, pwd, num) == 0)
		{
			free(list_head->value);
			list_head->value = ft_strdup(cwd);
			if (!list_head->value)
				return (NG);
			return (OK);
		}
		else if (list_head->next == NULL)
		{
			list_head->next = create_env_node(key_value);
			if (!list_head->next)
				return (NG);
			return (OK);
		}
		else if (list_head->next != NULL)
			list_head = list_head->next;
	}
	return (OK);
}

int	builtin_cd(char **args, t_env *list_head)
{
	struct stat	dir_stat;
	char		*path;
	char		*home;
	char		*cwd_old;
	char		*cwd_new;

	if (args[1] && args[2])
	{
		fprintf(stderr, " too many arguments\n");
		return (1);
	}
	if (!args[1])
	{
		home = getenv("HOME");
		if (!home)
		{
			fprintf(stderr, "minishell: cd: HOME not set\n");
			return (NG);
		}
	}
	else
		path = ft_strdup(args[1]);
	if (!path)
		return (NG);
	if (stat(path, &dir_stat) == -1)
	{
		fprintf(stderr, " No such file or directory\n");
		free(path);
		return (NG);
	}
	if (S_ISDIR(dir_stat.st_mode))
	{
		if (set_pwd(list_head, "OLDPWD", 6) == NG)
		{
			free(path);
			return (NG);
		}
		if (chdir(path) == NG)
		{
			fprintf(stderr, " chdir error\n");
			free(path);
			return (NG);
		}
		if (set_pwd(list_head, "PWD", 3) == NG)
		{
			free(path);
			return (NG);
		}
		free(path);
		return (OK);
	}
	else
	{
		fprintf(stderr, " Not a directory\n");
		free(path);
		return (NG);
	}
}
