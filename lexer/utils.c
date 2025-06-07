/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nando <nando@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 17:18:47 by nando             #+#    #+#             */
/*   Updated: 2025/05/29 18:03:32 by nando            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	quate_error(t_lexer *ctx)
{
	t_token	*token;

	printf("quate not closed.\n");
	free_buf(&ctx->buf);
	free_tokens(ctx->head);
}

int	ft_isspace(int c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r')
		return (1);
	else
		return (0);
}
