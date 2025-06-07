/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nando <nando@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 15:05:25 by nando             #+#    #+#             */
/*   Updated: 2025/06/07 18:10:35 by nando            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>
#include <stdlib.h>

static char	*create_key(char const *s, char c)
{
	char	*new_string;
	int		len;
	int		i;

	len = 0;
	i = 0;
	while (s[len] && s[len] != c)
		len++;
	new_string = malloc((len + 1) * sizeof(char));
	if (!new_string)
		return (NULL);
	while (i < len)
	{
		new_string[i] = s[i];
		i++;
	}
	new_string[i] = '\0';
	return (new_string);
}

static char	*create_value(char const *s)
{
	char	*new_string;
	int		len;
	int		i;

	len = 0;
	i = 0;
	while (s[len])
		len++;
	new_string = malloc((len + 1) * sizeof(char));
	if (!new_string)
		return (NULL);
	while (i < len)
	{
		new_string[i] = s[i];
		i++;
	}
	new_string[i] = '\0';
	return (new_string);
}

static void	free_inserted_memory(char **result, int j)
{
	j = j - 1;
	while (j >= 0)
	{
		free(result[j]);
		j--;
	}
	free(result);
}

static char	**create_split(char const *s, char **result, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	result[j] = create_key(&s[i], c);
	if (!result[j])
	{
		free_inserted_memory(result, j);
		return (NULL);
	}
	while (s[i] != '=')
		i++;
	i++;
	result[++j] = create_value(&s[i]);
	result[++j] = NULL;
	return (result);
}

char	**env_split(char const *s, char c)
{
	char	**result;

	if (!s)
		return (NULL);
	result = malloc(2 * sizeof(char *));
	if (!result)
		return (NULL);
	result = create_split(s, result, c);
	return (result);
}

t_env	*create_env_node(char **key_value)
{
	t_env	*env_node;

	env_node = malloc(sizeof(t_env));
	if (!env_node)
		return (NULL);
	env_node->key = ft_strdup(key_value[0]);
	if (!env_node->key)
		return (NULL);
	env_node->value = ft_strdup(key_value[1]);
	if (!env_node->value)
	{
		free(env_node->key);
		free(env_node);
		return (NULL);
	}
	env_node->flag = 1;
	env_node->next = NULL;
	return (env_node);
}

t_env	*init_env(char **envp)
{
	t_ctx	ctx;
	int		i;

	i = 0;
	ctx.head = NULL;
	ctx.tail = NULL;
	while (envp[i])
	{
		ctx.key_value = env_split(envp[i], '=');
		if (!ctx.key_value)
			return (NULL);
		if (ctx.key_value[1] == NULL)
			ctx.key_value[1] = ft_strdup("");
		ctx.node = create_env_node(ctx.key_value);
		if (ctx.head == NULL)
		{
			ctx.head = ctx.node;
			ctx.tail = ctx.node;
		}
		else
		{
			ctx.tail->next = ctx.node;
			ctx.tail = ctx.node;
		}
		i++;
	}
	return (ctx.head);
}

void	print_env_list(t_env *head)
{
	t_env	*cur;

	cur = head;
	while (cur)
	{
		printf("%s=%s\n", cur->key, cur->value);
		cur = cur->next;
	}
}

static void	print_env(char **envp)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
}

// int	main(int argc, char **argv, char **envp)
// {
// 	t_env	*env_head;

// 	(void)argc;
// 	(void)argv;
// 	print_env(envp);
// 	※　実際には、minishellのmainでこの下の1行を呼び出すと、minishell用の環境変数リストが作られるはず！
// 	env_head = init_env(envp);
// 	if (!env_head)
// 	{
// 		fprintf(stderr, "Failed to initialize environment list\n");
// 		return (1);
// 	}
// 	printf("============= ENV LIST CONTENTS ===========\n");
// 	print_env_list(env_head);
// 	return (0);
// }


//   TEST OK

