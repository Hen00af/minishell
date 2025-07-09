/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nando <nando@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 17:18:47 by nando             #+#    #+#             */
/*   Updated: 2025/07/09 10:52:05 by nando            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "lexer.h"

void	parent_error(t_lexer *ctx)
{
	ft_printf("parent not closed.\n");
	free_buf(&ctx->buf);
	free_tokens(ctx->head);
}

void	quate_error(t_lexer *ctx)
{
	ft_printf("quate not closed.\n");
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

int	is_valid_var_name(char *buf_word)
{
	int	i;

	i = 0;
	if (!(ft_isalpha(buf_word[i]) || buf_word[i] == '_'))
		return (0);
	i++;
	while (buf_word[i])
	{
		if (!(ft_isalnum(buf_word[i]) || buf_word[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

void	adjust_assign_word(t_token *head)
{
	t_token	*current;
	int		count;

	count = 0;
	current = head;
	while (current && current->type != TOK_EOF)
	{
		count++;
		current = current->next;
	}
	if (count == 1 && head->type == TOK_ASSIGN_WORD)
		return ;
	current = head;
	while (current && current->type != TOK_EOF)
	{
		if (current->type == TOK_ASSIGN_WORD)
			current->type = TOK_WORD;
		current = current->next;
	}
}
