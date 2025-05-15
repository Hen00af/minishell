/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nando <nando@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 20:08:16 by nando             #+#    #+#             */
/*   Updated: 2025/05/15 20:12:15 by nando            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

typedef enum e_tokentype
{
	TOK_WORD,
	TOK_PIPE,
	TOK_AND,
	TOK_OR,
	TOK_REDIR_IN,
	TOK_REDIR_OUT,
	TOK_HEREDOC,
	TOK_REDIR_APP,
	TOK_LPAREN,
	TOK_RPAREN,
	TOK_EOF
}	TokenType;

typedef struct s_token
{
	TokenType type; // WORD, PIPE, REDIR_IN…など
	char *text;     // 切り出した文字列
	struct s_token *next // 次トークンへのポインタ
}	t_token;

#endif LEXER_H