/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nando <nando@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 14:30:21 by nando             #+#    #+#             */
/*   Updated: 2025/06/25 21:49:54 by nando            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

typedef struct s_expand
{
	char	*expanded;
	char	**split_words;
	char	**new_argv;
	int		count_av;
	int		count_sw;
	int		expand_point;
	int		wild_flag;
}			t_expand;

char	*remove_quote(char *arg)
{
	size_t	strlen;
	char	*result;

	strlen = ft_strlen(arg);
	if (strlen < 2)
		return (ft_strdup(arg));
	if ((arg[0] == '\'' && arg[strlen - 1] == '\'') || (arg[0] == '\"'
			&& arg[strlen - 1] == '\"'))
	{
		result = malloc(sizeof(char) * (strlen - 1));
		if (!result)
			return (NULL);
		ft_strlcpy(result, arg + 1, strlen - 1);
		return (result);
	}
	return (ft_strdup(arg));
}

char	*expand_string(char *arg, t_env *env, t_expand *ctx, t_list *node)
{
	char			*cleaned_quote;
	char			*before;
	char			*tmp;
	t_redirection	*redir;

	redir = (t_redirection *)node->content;
	if (arg[0] == '\'')
	{
		redir->need_expand = true;
		cleaned_quote = remove_quote(arg);
		return (cleaned_quote);
	}
	else if (arg[0] == '\"')
	{
		redir->need_expand = true;
		cleaned_quote = remove_quote(arg);
		cleaned_quote = expand_variables(cleaned_quote, env);
		return (cleaned_quote);
	}
	redir->need_expand = false;
	before = ft_strdup(arg);
	arg = expand_variables(arg, env);
	arg = expand_tilda(arg, env);
	arg = expand_wild_card(arg);
	// free(arg);
	if (strcmp(before, arg) != 0)
		ctx->wild_flag = 1;
	free(before);
	return (ft_strdup(arg));
}

int	count_args(char **args)
{
	int	count;

	count = 0;
	while (args[count])
		count++;
	return (count);
}

void	create_new_args(t_command *cmd, t_expand *ctx, int i)
{
	int	j;
	int	k;
	int	l;

	j = 0;
	k = 0;
	while (j < i)
	{
		ctx->new_argv[j] = ft_strdup(cmd->argv[j]);
		j++;
	}
	while (k < ctx->count_sw)
	{
		ctx->new_argv[j + k] = ft_strdup(ctx->split_words[k]);
		k++;
	}
	ctx->expand_point = j + k;
	l = i + 1;
	while (cmd->argv[l])
	{
		ctx->new_argv[j + k] = ft_strdup(cmd->argv[l]);
		k++;
		l++;
	}
	ctx->new_argv[j + k] = NULL;
}

void	free_args(char **argv)
{
	int	i;

	i = 0;
	if (!argv)
		return ;
	while (argv[i])
		free(argv[i++]);
	free(argv);
}

void	expander(t_andor *ast, t_env *env)
{
	t_expand	ctx;
	t_list		*cmd_node;
	t_command	*cmd;
	int			i;

	i = 0;
	if (ast->type != ANDOR_PIPELINE)
		return ;
	cmd_node = ast->pipeline->commands;
	while (cmd_node)
	{
		i = 0;
		cmd = (t_command *)cmd_node->content;
		if (cmd && cmd->argv[i])
		{
			while (cmd->argv && cmd->argv[i])
			{
				ctx.wild_flag = 0;
				ctx.expanded = expand_string(cmd->argv[i], env, &ctx,
						ast->pipeline->commands);
				if (ctx.wild_flag)
				{
					ctx.split_words = ft_split(ctx.expanded, " ");
					ctx.count_av = count_args(cmd->argv);
					ctx.count_sw = count_args(ctx.split_words);
					ctx.new_argv = malloc(sizeof(char *) * (ctx.count_av
								+ ctx.count_sw));
					create_new_args(cmd, &ctx, i);
					free_args(cmd->argv);
					i = ctx.expand_point;
					cmd->argv = ctx.new_argv;
					free_args(ctx.split_words);
					ctx.expanded = NULL;
					continue ;
				}
				free(cmd->argv[i]);
				cmd->argv[i] = ft_strdup(ctx.expanded);
				ctx.expanded = NULL;
				i++;
			}
		}
		cmd_node = cmd_node->next;
	}
}

void	expand_andor_arguments(t_andor *ast, t_env *env)
{
	if (!ast)
		return ;
	if (ast->type == ANDOR_PIPELINE)
		expander(ast, env);
	else
	{
		expand_andor_arguments(ast->left, env);
		expand_andor_arguments(ast->right, env);
	}
}

// ====== MAIN ======
// int	main(int ac, char **av, char **envp)
// {
// 	t_token	*lex;
// 	t_ast	*ast;
// 	t_andor	*linearized_ast;
// 	t_env	*env;

// 	if (ac < 2)
// 		return (0);
// 	lex = lexer(av[1]);
// 	ast = start_parse(lex);
// 	// print_ast(ast, 0);
// 	linearized_ast = linearizer(ast);
// 	env = init_env(envp);
// 	expander(linearized_ast, env);
// 	print_linerlized_ast(linearized_ast, 0);
// 	return (0);
// }

//////////////////////////////////////////////////////////////////////////////
// test code /////////////////////////////////////////////////////////
// typedef struct s_testcase
// {
// 	char	*input;
// 	char	*expected;
// }			t_testcase;

// t_env	*create_env(char *key, char *value)
// {
// 	t_env	*env;

// 	env = malloc(sizeof(t_env));
// 	env->key = ft_strdup(key);
// 	env->value = ft_strdup(value);
// 	env->flag = 0;
// 	env->next = NULL;
// 	return (env);
// }

// // 環境変数リストを構築
// t_env	*setup_env_list(void)
// {
// 	t_env	*head;

// 	head = create_env("USER", "nando");
// 	head->next = create_env("HOME", "/home/nando");
// 	head->next->next = create_env("SHELL", "/bin/bash");
// 	return (head);
// }

// // メモリ解放
// void	free_env_list(t_env *env)
// {
// 	t_env	*tmp;

// 	while (env)
// 	{
// 		tmp = env->next;
// 		free(env->key);
// 		free(env->value);
// 		free(env);
// 		env = tmp;
// 	}
// }
// t_testcase	test_cases[] = {
// 	// === 変数展開 ===
// 	{"$USER", "nando"},
// 	{"$HOME", "/home/nando"},
// 	{"$SHELL", "/bin/bash"},
// 	{"$UNDEF", ""},

// 	// === ワイルドカード展開（※ファイル名は環境依存） ===
// 	{"*.c", "[depends on dir]"},
// 	{"abc*", "[depends on dir]"},
// 	{"no_match*", "no_match*"},

// 	// === シングルクォート（展開しない） ===
// 	{"'$USER'", "$USER"},
// 	{"'*.c'", "*.c"},
// 	{"'abc*'", "abc*"},

// 	// === ダブルクォート（変数のみ展開） ===
// 	{"\"$USER\"", "nando"},
// 	{"\"*.c\"", "*.c"}, // ワイルドカードは展開されない
// 	{"\"$USER:$SHELL\"", "nando:/bin/bash"},

// 	// === echo + 複合パターン（各トークン単位で渡す） ===
// 	{"echo", "echo"},
// 	{"\"*.c\"", "*.c"},
// 	{"'*.c'", "*.c"},
// 	{"*.c", "[depends on dir]"},
// 	{"\"$USER:$SHELL\"", "nando:/bin/bash"},
// 	{"'$USER:$SHELL'", "$USER:$SHELL"},

// 	// === 無効な変数名や混合 ===
// 	{"$U*ER", "*ER"},     // ← $U が未定義 → *ER に展開 → ワイルドカード展開対象
// 	{"\"$U*ER\"", "*ER"}, // ← ダブルクォート内でも同様に展開される
// 	{"'$U*ER'", "$U*ER"}, // ← シングルクォート → 展開されない

// 	// === チルダ展開 ===
// 	{"~", "/home/nando"},
// 	{"~/projects", "/home/nando/projects"},

// 	{NULL, NULL}};
// void	test_expand_string(t_env *env_list)
// {
// 	int			i;
// 	char		*result;
// 	t_expand	ctx;

// 	printf("==== Testing expand_string() (per token) ====\n");
// 	for (i = 0; test_cases[i].input; i++)
// 	{
// 		printf("Test #%02d\n", i + 1);
// 		printf("Input    : \"%s\"\n", test_cases[i].input);
// 		printf("Expected : \"%s\"\n", test_cases[i].expected);
// 		// 初期化
// 		ctx.wild_flag = 0;
// 		ctx.expanded = NULL;
// 		ctx.split_words = NULL;
// 		ctx.new_argv = NULL;
// 		ctx.count_av = 0;
// 		ctx.count_sw = 0;
// 		ctx.expand_point = 0;
// 		result = expand_string(ft_strdup(test_cases[i].input), env_list, &ctx);
// 		printf("Expanded : \"%s\"\n", result);
// 		if (strcmp(test_cases[i].expected, "[depends on dir]") == 0
// 			|| strcmp(result, test_cases[i].expected) == 0)
// 			printf("✅ Match!\n");
// 		else
// 			printf("❌ Mismatch!\n");
// 		printf("-------------------------------\n");
// 		free(result);
// 	}
// }

// int	main(void)
// {
// 	t_env	*env_list;

// 	env_list = setup_env_list();
// 	test_expand_string(env_list);
// 	free_env_list(env_list);
// 	return (0);
// }

////////////////////////////////////////////////////////////////////////////////////////

// char	**make_argv(const char *args[])
// {
// 	char	**argv;

// 	int i, count;
// 	for (count = 0; args[count]; count++)
// 		;
// 	argv = malloc(sizeof(char *) * (count + 1));
// 	for (i = 0; i < count; i++)
// 		argv[i] = ft_strdup(args[i]);
// 	argv[i] = NULL;
// 	return (argv);
// }

// void	free_argv(char **argv)
// {
// 	int	i;

// 	i = 0;
// 	if (!argv)
// 		return ;
// 	while (argv[i])
// 		free(argv[i++]);
// 	free(argv);
// }

// t_line	*create_line_node(t_node_type type, const char *args[],
// 		const char *filename)
// {
// 	t_line	*node;

// 	node = malloc(sizeof(t_line));
// 	if (!node)
// 		return (NULL);
// 	node->type = type;
// 	node->argv = make_argv(args);
// 	node->filename = filename ? ft_strdup(filename) : NULL;
// 	node->next = NULL;
// 	return (node);
// }

// void	free_nodes(t_line *node)
// {
// 	t_line	*tmp;

// 	while (node)
// 	{
// 		tmp = node->next;
// 		free_argv(node->argv);
// 		if (node->filename)
// 			free(node->filename);
// 		free(node);
// 		node = tmp;
// 	}
// }

// void	print_node(t_line *node)
// {
// 	int	i;

// 	i = 0;
// 	while (node)
// 	{
// 		printf("NODE (type=%d):\n", node->type);
// 		if (node->argv)
// 		{
// 			while (node->argv[i])
// 			{
// 				printf("  argv[%d]: \"%s\"\n", i, node->argv[i]);
// 				i++;
// 			}
// 		}
// 		if (node->filename)
// 			printf("  filename: \"%s\"\n", node->filename);
// 		printf("--------\n");
// 		i = 0;
// 		node = node->next;
// 	}
// }

// // === 環境変数 ===

// t_env	*create_env(char *key, char *value)
// {
// 	t_env	*env;

// 	env = malloc(sizeof(t_env));
// 	if (!env)
// 		return (NULL);
// 	env->key = ft_strdup(key);
// 	env->value = ft_strdup(value);
// 	env->flag = 0;
// 	env->next = NULL;
// 	return (env);
// }

// t_env	*setup_env_list(void)
// {
// 	t_env	*head;

// 	head = create_env("USER", "nando");
// 	head->next = create_env("HOME", "/home/nando");
// 	head->next->next = create_env("SHELL", "/bin/bash");
// 	return (head);
// }

// void	free_env_list(t_env *env)
// {
// 	t_env	*tmp;

// 	while (env)
// 	{
// 		tmp = env->next;
// 		free(env->key);
// 		free(env->value);
// 		free(env);
// 		env = tmp;
// 	}
// }

// // === テスト本体 ===

// void	test_expander(void)
// {
// 	t_env		*env;
// 	const char	*args1[] = {"echo", "\"$USER:$SHELL\"", NULL};
// 	t_line		*n1;
// 	const char	*args2[] = {"echo", "'*.c'", NULL};
// 	t_line		*n2;
// 	const char	*args3[] = {"echo", "*.c", NULL};
// 	t_line		*n3;
// 	const char	*args4[] = {"cat", NULL};
// 	t_line		*n4;

// 	env = setup_env_list();
// 	// ノード1: echo "$USER:$SHELL"
// 	n1 = create_line_node(NODE_COMMAND, args1, NULL);
// 	// ノード2: echo '*.c'（シングルクォート）
// 	n2 = create_line_node(NODE_COMMAND, args2, NULL);
// 	n1->next = n2;
// 	// ノード3: echo *.c（ワイルドカード展開）
// 	n3 = create_line_node(NODE_COMMAND, args3, NULL);
// 	n2->next = n3;
// 	// ノード4: 入力ファイル名が変数で構成されているケース
// 	n4 = create_line_node(NODE_REDIR_IN, args4, "$HOME/input.txt");
// 	n3->next = n4;
// 	// === Before ===
// 	printf("=== Before expander ===\n");
// 	print_node(n1);
// 	// === Run ===
// 	expander(n1, env);
// 	// === After ===
// 	printf("=== After expander ===\n");
// 	print_node(n1);
// 	// === Cleanup ===
// 	free_nodes(n1);
// 	free_env_list(env);
// }

// int	main(void)
// {
// 	test_expander();
// 	return (0);
// }

/////////////////////////////////////////////////////////////////////////////////////////////////////
// static t_env	*make_env(char *key, char *value)
// {
// 	t_env	*env;

// 	env = malloc(sizeof(t_env));
// 	env->key = ft_strdup(key);
// 	env->value = ft_strdup(value);
// 	env->flag = 0;
// 	env->next = NULL;
// 	return (env);
// }

// static t_env	*init_envs(void)
// {
// 	t_env	*e1;
// 	t_env	*e2;

// 	e1 = make_env("HOME", "/home/testuser");
// 	e2 = make_env("USER", "nando");
// 	e1->next = e2;
// 	return (e1);
// }

// // コマンドノード作成
// static t_list	*make_command_node(char **argv)
// {
// 	t_command	*cmd;

// 	cmd = malloc(sizeof(t_command));
// 	cmd->argv = argv;
// 	cmd->redirections = NULL;
// 	cmd->subshell_ast = NULL;
// 	return (ft_lstnew(cmd));
// }

// // ANDOR_PIPELINE ノード作成
// static t_andor	*make_pipeline_node(char **argv)
// {
// 	t_pipeline	*pipe;
// 	t_andor		*andor;

// 	pipe = malloc(sizeof(t_pipeline));
// 	pipe->commands = NULL;
// 	ft_lstadd_back(&pipe->commands, make_command_node(argv));
// 	andor = malloc(sizeof(t_andor));
// 	andor->type = ANDOR_PIPELINE;
// 	andor->pipeline = pipe;
// 	return (andor);
// }

// // AND/OR ノード作成
// static t_andor	*make_andor_node(t_andor_type type, t_andor *left,
// 		t_andor *right)
// {
// 	t_andor	*andor;

// 	andor = malloc(sizeof(t_andor));
// 	andor->type = type;
// 	andor->left = left;
// 	andor->right = right;
// 	return (andor);
// }

// // argv 表示
// static void	print_argv(char **argv)
// {
// 	for (int i = 0; argv && argv[i]; i++)
// 		printf("argv[%d] = %s\n", i, argv[i]);
// }

// // AST 内を再帰的に表示
// static void	print_andor(t_andor *a)
// {
// 	t_command	*cmd;

// 	if (!a)
// 		return ;
// 	if (a->type == ANDOR_PIPELINE)
// 	{
// 		cmd = (t_command *)a->pipeline->commands->content;
// 		print_argv(cmd->argv);
// 	}
// 	else
// 	{
// 		print_andor(a->left);
// 		print_andor(a->right);
// 	}
// }

// // テストの実行
// static void	run_andor_test(int num, t_andor *ast, t_env *env)
// {
// 	printf("\n===== TEST %d =====\n", num);
// 	printf("Before expansion:\n");
// 	print_andor(ast);
// 	expand_andor_arguments(ast, env);
// 	printf("After expansion:\n");
// 	print_andor(ast);
// }

// int	main(void)
// {
// 	t_env *env = init_envs();

// 	// === TEST 1: $HOME ===
// 	char **argv1 = malloc(sizeof(char *) * 3);
// 	argv1[0] = ft_strdup("echo");
// 	argv1[1] = ft_strdup("$HOME");
// 	argv1[2] = NULL;
// 	run_andor_test(1, make_pipeline_node(argv1), env);

// 	// === TEST 2: ~ ===
// 	char **argv2 = malloc(sizeof(char *) * 3);
// 	argv2[0] = ft_strdup("cd");
// 	argv2[1] = ft_strdup("~");
// 	argv2[2] = NULL;
// 	run_andor_test(2, make_pipeline_node(argv2), env);

// 	// === TEST 3: double quoted variable ===
// 	char **argv3 = malloc(sizeof(char *) * 3);
// 	argv3[0] = ft_strdup("echo");
// 	argv3[1] = ft_strdup("\"$HOME/dir\"");
// 	argv3[2] = NULL;
// 	run_andor_test(3, make_pipeline_node(argv3), env);

// 	// === TEST 4: single quoted variable (no expansion) ===
// 	char **argv4 = malloc(sizeof(char *) * 3);
// 	argv4[0] = ft_strdup("echo");
// 	argv4[1] = ft_strdup("'$HOME/dir'");
// 	argv4[2] = NULL;
// 	run_andor_test(4, make_pipeline_node(argv4), env);

// 	// === TEST 5: wildcard ===
// 	char **argv5 = malloc(sizeof(char *) * 3);
// 	argv5[0] = ft_strdup("ls");
// 	argv5[1] = ft_strdup("*.c");
// 	argv5[2] = NULL;
// 	run_andor_test(5, make_pipeline_node(argv5), env);

// 	// === TEST 6: AND構造 (echo $HOME && echo ~) ===
// 	char **a6_1 = malloc(sizeof(char *) * 3);
// 	a6_1[0] = ft_strdup("echo");
// 	a6_1[1] = ft_strdup("$HOME");
// 	a6_1[2] = NULL;

// 	char **a6_2 = malloc(sizeof(char *) * 3);
// 	a6_2[0] = ft_strdup("echo");
// 	a6_2[1] = ft_strdup("~");
// 	a6_2[2] = NULL;

// 	run_andor_test(6, make_andor_node(ANDOR_AND, make_pipeline_node(a6_1),
// 			make_pipeline_node(a6_2)), env);

// 	// === TEST 7: OR構造 + シングルクオート + ワイルドカード ===
// 	char **a7_1 = malloc(sizeof(char *) * 3);
// 	a7_1[0] = ft_strdup("echo");
// 	a7_1[1] = ft_strdup("'$USER'");
// 	a7_1[2] = NULL;
// 	char **a7_2 = malloc(sizeof(char *) * 3);
// 	a7_2[0] = ft_strdup("echo");
// 	a7_2[1] = ft_strdup("*.c");
// 	a7_2[2] = NULL;
// 	run_andor_test(7, make_andor_node(ANDOR_OR, make_pipeline_node(a7_1),
// 			make_pipeline_node(a7_2)), env);

// 	// === TEST 8: ネスト構造 ( (echo $USER && echo $HOME) || echo *.h ) ===
// 	t_andor *t8_left = make_andor_node(ANDOR_AND, make_pipeline_node(a7_1),
// 			make_pipeline_node(a6_1));
// 	run_andor_test(8, make_andor_node(ANDOR_OR, t8_left,
// 			make_pipeline_node((char *[]){"echo", "*.h", NULL})), env);

// 	// 環境変数解放
// 	free(env->next->key);
// 	free(env->next->value);
// 	free(env->next);
// 	free(env->key);
// 	free(env->value);
// 	free(env);
// 	return (0);
// }