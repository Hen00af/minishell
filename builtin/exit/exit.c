/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nando <nando@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 15:28:33 by nando             #+#    #+#             */
/*   Updated: 2025/06/07 19:10:13 by nando            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../builtin.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_exit
{
	int		exit_status;
}			t_exit;

static int	count_args(char **args)
{
	int	count;

	count = 0;
	while (args[count])
		count++;
	return (count);
}

static int	is_numeric(const char *str)
{
	int	i;

	i = 0;
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static void	handle_not_numeric(int exit_status, char *arg)
{
	printf("minishell: exit: %s: numeric argument required\n", arg);
	exit_status = 255;
	exit(exit_status);
}

//現状はintポインタ型で渡しているが、minishell構造体を渡してその中の"int exit_status"へアクセスさせる
static void	handle_exit_argument(t_exit *exit_s, char *arg)
{
	if (!is_numeric(arg))
		handle_not_numeric(exit_s->exit_status, arg);
	exit_s->exit_status = ft_atoi(arg);
	exit_s->exit_status = exit_s->exit_status % 256;
	if (exit_s->exit_status < 0)
		exit_s->exit_status += 256;
	exit(exit_s->exit_status);
}

int	builtin_exit(char **args)
{
	t_exit	*exit_s;
	int		count;

	exit_s = malloc(sizeof(t_exit));
	//　　　⇩　この変数はminishell構造体に含めて参照できるようにする
	count = count_args(args);
	printf("exit\n");
	//このように引数を2つ以上与えるとbashはexitせずに、終了ステータスのみ更新（1に）してそのままbashを継続する。
	//その後bashでecho $?をすると、1が表示される。
	if (count > 2)
		return (NG);
	else if (count == 1)
		exit(0);
	else if (count == 2)
		handle_exit_argument(exit_s, args[1]);
	return (OK);
}

// この関数はテスト時に呼び出されるため、exit()の呼び出しで
// 実際にはプロセスが終了するので、1テストずつ手動実行 or bashで逐次実行が推奨です。

int	main(void)
{
	// // 1️⃣ 引数なし（正常終了）
	// char *args1[] = {"exit", NULL};
	// printf("\n===== Test 1: exit with no argument =====\n");
	// builtin_exit(args1);

	// // 2️⃣ 数値引数あり（正常終了）
	// char *args2[] = {"exit", "42", NULL};
	// printf("\n===== Test 2: exit with valid numeric argument =====\n");
	// builtin_exit(args2);

	// // 3️⃣ 数値引数あり（負数）
	// char *args3[] = {"exit", "-5", NULL};
	// printf("\n===== Test 3: exit with negative numeric argument =====\n");
	// builtin_exit(args3);

	// // 4️⃣ 数値引数が非数字（エラー終了）
	// char *args4[] = {"exit", "abc", NULL};
	// printf("\n===== Test 4: exit with non-numeric argument =====\n");
	// builtin_exit(args4);

	// // 5️⃣ 引数が多すぎる（too many arguments）
	// char *args5[] = {"exit", "1", "extra", NULL};
	// printf("\n===== Test 5: exit with too many arguments =====\n");
	// builtin_exit(args5);

	return (0);
}