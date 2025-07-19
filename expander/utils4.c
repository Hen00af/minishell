/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nando <nando@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 23:28:24 by nando             #+#    #+#             */
/*   Updated: 2025/07/19 18:05:13 by nando            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

char	*remove_quote(char *arg)
{
	size_t	len;
	char	*res;

	len = ft_strlen(arg);
	if (len >= 2 && ((arg[0] == '\'' && arg[len - 1] == '\'') || (arg[0] == '\"'
				&& arg[len - 1] == '\"')))
	{
		res = malloc(len - 1);
		if (!res)
			return (NULL);
		ft_strlcpy(res, arg + 1, len - 1);
		return (res);
	}
	return (ft_strdup(arg));
}

int	count_quote_in_arg(char *arg, size_t len)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (i < len)
	{
		if (arg[i] != '\'' && arg[i] != '\"')
			count++;
		i++;
	}
	return (count);
}

char	*remove_all_quote(char *arg)
{
	char	*res;
	size_t	len;
	size_t	i;
	size_t	count;

	len = ft_strlen(arg);
	count = count_quote_in_arg(arg, len);
	res = malloc(sizeof(char) * (count + 1));
	memset(res, 0, count + 1);
	i = 0;
	count = 0;
	while (i < len)
	{
		if (arg[i] != '\'' && arg[i] != '\"')
		{
			res[count] = arg[i];
			count++;
		}
		i++;
	}
	res[count] = '\0';
	return (res);
}

char	*expand_all_type(char *arg, t_shell *shell, t_expand *ctx)
{
	char	*tmp1;
	char	*tmp2;
	char	*result;

	tmp1 = expand_variables(arg, shell);
	tmp2 = expand_tilda(tmp1, shell->env);
	free(tmp1);
	result = expand_wild_card(tmp2, ctx);
	free(tmp2);
	return (result);
}

void	expand_and_add_to_output(t_expand *ctx, t_shell *shell, int state,
		int num)
{
	char	*after;
	char	*old_out;

	if (num == 1 || num == 2)
		after = expand_all_type(buf_flush(&ctx->buf), shell, ctx);
	else if (num == 3)
		after = expand_variables(remove_quote(buf_flush(&ctx->buf)), shell);
	else if (num == 4)
		after = remove_quote(buf_flush(&ctx->buf));
	old_out = ctx->output;
	ctx->output = ft_strjoin(old_out, after);
	free(old_out);
	free(after);
	ctx->state = state;
}
