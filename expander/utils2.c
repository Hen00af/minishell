/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nando <nando@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 17:12:10 by nando             #+#    #+#             */
/*   Updated: 2025/06/26 20:45:33 by nando            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

char	*remove_quote(bool need_expand, char *arg)
{
	size_t	strlen;
	char	*result;

	need_expand = true;
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

void	create_new_args(t_expand *ctx, t_command *cmd, int i)
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

void	generate_wildcard_matches(t_expand *ctx, t_command *cmd, int *i)
{
	ctx->split_words = ft_split(ctx->expanded, " ");
	ctx->count_av = count_args(cmd->argv);
	ctx->count_sw = count_args(ctx->split_words);
	ctx->new_argv = malloc(sizeof(char *) * ((ctx->count_av + ctx->count_sw)
				+ 1));
	create_new_args(ctx, cmd, *i);
	free_args(cmd->argv);
	*i = ctx->expand_point;
	cmd->argv = ctx->new_argv;
	free_args(ctx->split_words);
	ctx->expanded = NULL;
	return ;
}
