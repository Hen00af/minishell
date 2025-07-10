/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nando <nando@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 23:28:24 by nando             #+#    #+#             */
/*   Updated: 2025/07/10 23:56:50 by nando            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static char	*clean_outer_quotes(const char *arg)
{
	size_t	len;
	char	start;
	char	end;
	char	*res;

	len = ft_strlen(arg);
	if (len < 2)
		return (ft_strdup(arg));
	start = arg[0];
	end = arg[len - 1];
	if ((start == '\'' && end == '\'') || (start == '\"' && end == '\"'))
	{
		res = malloc(len - 1);
		if (!res)
			return (NULL);
		ft_strlcpy(res, arg + 1, len - 1);
		return (res);
	}
	return (ft_strdup(arg));
}

char	*remove_quote(char *arg)
{
	char	*res;

	res = clean_outer_quotes(arg);
	free(arg);
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
