/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nando <nando@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 14:30:21 by nando             #+#    #+#             */
/*   Updated: 2025/06/17 09:38:18 by nando            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

char	*expand_string(char *arg, t_env *env)
{
	int	i;

	i = 0;
	ft_printf("default arg = %s\n", arg);
	if (arg[i] == '\'')
	{
		printf("[single quote]no expanded arg = %s\n", arg);
		return (arg);
	}
	else if (arg[i] == '\"')
	{
		arg = expand_variables(arg, env);
		printf("[double quote]expanded variables arg = %s\n", arg);
		return (arg);
	}
	arg = expand_variables(arg, env);
	printf("[none quote]expanded variables arg = %s\n", arg);
	arg = expand_tilda(arg, env);
	printf("[none quote]expanded tilda arg = %s\n", arg);
	arg = expand_wild_card(arg);
	printf("[none quote]expanded wild_card arg = %s\n", arg);
	return (arg);
}

void	expander(t_line *node, t_env *env)
{
	int	i;

	i = 0;
	while (node)
	{
		if (node->type == NODE_COMMAND)
		{
			while (node->argv && node->argv[i])
			{
				node->argv[i] = expand_string(node->argv[i], env);
				i++;
			}
		}
		node = node->next;
	}
}

//////////////////////////////////////////////////////////////////////////////
//     test  code    /////////////////////////////////////////////////////////
typedef struct s_testcase
{
	char	*input;
	char	*expected;
}			t_testcase;

t_env	*create_env(char *key, char *value)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	env->key = ft_strdup(key);
	env->value = ft_strdup(value);
	env->flag = 0;
	env->next = NULL;
	return (env);
}

// 環境変数リストを構築
t_env	*setup_env_list(void)
{
	t_env	*head;

	head = create_env("USER", "nando");
	head->next = create_env("HOME", "/home/nando");
	head->next->next = create_env("SHELL", "/bin/bash");
	return (head);
}

// メモリ解放
void	free_env_list(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		free(env->key);
		free(env->value);
		free(env);
		env = tmp;
	}
}

void	test_expand_string(t_env *env_list)
{
	int		i;
	char	*result;

	t_testcase test_cases[] = {// --- 変数展開のみ ---
								{"Hello $USER", "Hello nando"},
								{"$HOME is where the heart is",
									"/home/nando is where the heart is"},
								{"Undefined: $UNDEF", "Undefined:"},
								// --- ワイルドカード（この結果は実行環境に依存） ---
								{"*.c", "[depends on dir]"},
								{"abc*", "[depends on dir]"},
								{"no_match*", "no_match*"},
								// --- クォート付きワイルドカード（展開しない） ---
								{"\"*.c\"", "*.c"},
								{"'*.c'", "*.c"},
								// --- クォート付き変数展開 ---
								{"\"$USER\"", "nando"},
								{"'$USER'", "$USER"},
								// --- クォートとワイルドカードの混合 ---
								{"echo \"*.c\"", "echo *.c"},
								{"echo '*.c'", "echo *.c"},
								{"echo *.c", "[depends on dir]"},
								// --- 複合パターン ---
								{"$USER*.c", "[depends on dir]"},
								{"$USER:$SHELL *.h", "[depends on dir]"},
								{"\"$USER:$SHELL\" *.h", "[depends on dir]"},
								{"echo '$USER:$SHELL'", "echo $USER:$SHELL"},
								// --- 変数名の途中にワイルドカード ---
								{"$U*ER", "$U*ER"},
								{NULL, NULL}};
	printf("==== Testing expand_string() (with expected output) ====\n");
	for (i = 0; test_cases[i].input; i++)
	{
		printf("Test #%d\n", i + 1);
		printf("Input    : \"%s\"\n", test_cases[i].input);
		printf("Expected : \"%s\"\n", test_cases[i].expected);
		result = expand_string(ft_strdup(test_cases[i].input), env_list);
		printf("Expanded : \"%s\"\n", result);
		if (strcmp(result, test_cases[i].expected) == 0
			|| strcmp(test_cases[i].expected, "[depends on dir]") == 0)
			printf("✅ Match!\n");
		else
			printf("❌ Mismatch!\n");
		printf("-------------------------------\n");
		free(result);
	}
}

int	main(void)
{
	t_env	*env_list;

	env_list = setup_env_list();
	test_expand_string(env_list);
	free_env_list(env_list);
	return (0);
}
