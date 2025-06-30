/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nando <nando@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 15:02:10 by nando             #+#    #+#             */
/*   Updated: 2025/06/30 18:19:22 by nando            ###   ########.fr       */
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

	if (!args[1])
	{
		path = getenv("HOME");
		if (!path)
		{
			printf("minishell: cd: HOME not set\n");
			return (NG);
		}
	}
	else
		path = ft_strdup(args[1]);
	if (stat(path, &dir_stat) == -1)
	{
		printf("minishell: cd: %s: No such file or directory\n", path);
		return (NG);
	}
	if (S_ISDIR(dir_stat.st_mode))
	{
		if (set_pwd(list_head, "OLDPWD", 6) == NG)
			return (NG);
		if (chdir(path) == NG)
		{
			printf("minishell: cd: %s:chdir error\n", path);
			return (NG);
		}
		if (set_pwd(list_head, "PWD", 3) == NG)
			return (NG);
		return (OK);
	}
	else
	{
		printf("minishell: cd: %s: Not a directory\n", path);
		return (NG);
	}
	return (OK);
}

// int	main(int argc, char **argv, char **envp)
// {
// 	t_env	*env_head;
// 	char	*args1[] = {"cd", "/tmp", NULL};
// 	char	*args2[] = {"cd", "/nonexistent", NULL};
// 	char	*args3[] = {"cd", "/etc/hosts", NULL};
// 	char	*args4[] = {"cd", "/home/nando", NULL};

// 	(void)argc;
// 	(void)argv;
// 	// 1️⃣ 環境変数リストを初期化
// 	env_head = init_env(envp);
// 	if (!env_head)
// 	{
// 		fprintf(stderr, "Failed to initialize environment list\n");
// 		return (1);
// 	}
// 	// 2️⃣ 実行前の環境変数表示
// 	printf("========================== Before cd ====================\n");
// 	print_env_list(env_head);
// 	// 3️⃣ テスト: cd /tmp
// 	printf("\n--------------------- Test 1: cd /tmp -------------------\n");
// 	builtin_cd(args1, env_head);
// 	print_env_list(env_head);
// 	// 4️⃣ テスト: cd /nonexistent
// 	printf("\n--------------------- Test 2: cd/nonexistent -------------------\n");
// 	builtin_cd(args2, env_head);
// 	print_env_list(env_head);
// 	// 5️⃣ テスト: cd /etc/hosts (ファイル)
// 	printf("\n--------------------- Test 3: cd/etc/hosts ---------------------\n");
// 	builtin_cd(args3, env_head);
// 	print_env_list(env_head);
// 	// ⑥ テスト: cd /bin/ls
// 	printf("\n--------------------- Test 4: cd
// home / nando-- -----------------\n ");
// 	builtin_cd(args4, env_head);
// 	print_env_list(env_head);
// 	// 6️⃣ メモリ解放（省略、必要なら実装）
// 	return (0);
// }
