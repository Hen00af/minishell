/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buf2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nando <nando@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 20:20:56 by shattori          #+#    #+#             */
/*   Updated: 2025/07/08 14:08:49 by nando            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./lexer.h"

void	buf_add_and_assign_flag(t_lexer *ctx, char c)
{
	buf_add(&ctx->buf, c);
	ctx->assignment_flag = 1;
}

void	buf_add_and_set_state(t_lexer *ctx, char c)
{
	buf_add(&ctx->buf, c);
	ctx->state = STA_IN_WORD;
}
