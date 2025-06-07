/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nando <nando@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 15:57:37 by nando             #+#    #+#             */
/*   Updated: 2025/06/07 16:47:51 by nando            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "utils.h"

void	free_environ(char **environ, int i)
{
	i--;
	while (i >= 0)
	{
		free(environ[i]);
		i--;
	}
	free(environ);
	return ;
}

int	count_env_list(t_env *list_head)
{
	int	i;

	i = 0;
	while (list_head)
	{
		printf("key = %s, value = %s, flag = %d\n", list_head->key,
			list_head->value, list_head->flag);
		if (list_head->flag == 1)
			i++;
		list_head = list_head->next;
	}
	return (i);
}

int	create_env_array(char **environ, t_env *list_head)
{
	char	*key_value;
	char	*tmp;
	int		i;

	i = 0;
	while (list_head)
	{
		if (list_head->flag == 1)
		{
			tmp = ft_strjoin(list_head->key, "=");
			key_value = ft_strjoin(tmp, list_head->value);
			free(tmp);
			environ[i] = ft_strdup(key_value);
			if (!environ[i])
			{
				free_environ(environ, i);
				return (ERROR);
			}
			free(key_value);
		}
		list_head = list_head->next;
		i++;
	}
	return (0);
}

char	**env_to_array(t_env *list_head)
{
	t_env	*env_tmp;
	char	**environ;
	int		i;

	env_tmp = list_head;
	i = count_env_list(list_head);
	environ = malloc(sizeof(char *) * (i + 1));
	if (!environ)
		return (NULL);
	list_head = env_tmp;
	if (create_env_array(environ, list_head) == ERROR)
		return (NULL);
	environ[i] = NULL;
	return (environ);
}

t_env	*create_test_env(char *key, char *value)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = key;
	node->value = value;
	node->flag = 1;
	node->next = NULL;
	return (node);
}



// このmainは"assign_shell_var()"のテストも兼ねている。

// int	main(void)
// {
// 	t_env	*env_head;
// 	t_env	*node2;
// 	char	**env_array;
// 	int		i;

// 	①　テスト用の環境変数リスト作成
// 	env_head = create_test_env("USER", "nando");
// 	node2 = create_test_env("PWD", "/home/nando");
// 	env_head->next = node2;

//  ②　assign_shell_var()のテスト
// 	assign_shell_var("FOO=naruki", env_head);

//  ③　env_to_array()のテスト
// 	env_array = env_to_array(env_head);

//　④　結果表示
// 	if (!env_array)
// 	{
// 		printf("env_to_array() failed\n");
// 		return (1);
// 	}
// 	i = 0;
// 	while (env_array[i])
// 	{
// 		printf("env_array[%d] = %s\n", i, env_array[i]);
// 		i++;
// 	}

// 	⑤メモリ解放
// 	i = 0;
// 	while (env_array[i])
// 	{
// 		free(env_array[i]);
// 		i++;
// 	}
// 	free(env_array);
// 	ノードの解放（今回はテストなので key, value は解放不要）
// 	free(env_head);
// 	free(node2);
// 	return (0);
// }
