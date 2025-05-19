/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nando <nando@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 20:23:45 by nando             #+#    #+#             */
/*   Updated: 2025/05/19 20:32:25 by nando            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/////////////////////////////
typedef enum e_tokentype //トークンタイプ
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
	TOK_EOF,
	TOK_NUL
}			TokenType;

//////////////////////////////
typedef enum e_statetype //状態管理
{
	STA_DEFAULT,
	STA_IN_WORD,
	STA_IN_SQUOTE,
	STA_IN_DQUOTE,
	STA_IN_VARIABLE,
}			StateType;

//////////////////////////////
typedef struct s_token //トークン構造体
{
	TokenType type;       // WORD, PIPE, REDIR_IN…など
	char *text;           // 切り出した文字列
	struct s_token *next; // 次トークンへのポインタ
}			t_token;

/////////////////////////////
typedef struct s_buf
{
	char	*word;
	size_t	len;
	size_t	capa;
}			t_buf;

t_token	*create_token(TokenType type, char *word)
{
	t_token	*token;

	token = malloc(sizeof *token);
	if (!token)
		return (NULL);
	token->type = type;
	token->text = word;
	token->next = NULL;
	return (token);
}

void	buf_init(t_buf *buf)
{
	buf->capa = 1;
	buf->len = 0;
	buf->word = malloc(buf->capa);
	if (buf->word)
		buf->word[0] = '\0';
}

void	buf_add(t_buf *buf, char c)
{
	char	*new_word;
	size_t	new_capa;

	if (buf->capa <= (buf->len + 1))
	{
		new_capa = buf->capa * 2;
		new_word = malloc(new_capa);
		if (!new_word)
			return ;
		memcpy(new_word, buf->word, buf->len);
		free(buf->word);
		buf->word = new_word;
		buf->capa = new_capa;
	}
	buf->word[buf->len++] = c;
	buf->word[buf->len] = '\0';
}

char	*buf_flush(t_buf *buf, t_token *token)
{
	char	*text;

	text = buf->word;
	buf_init(buf);
	return (text);
}

void	free_buf(t_buf *buf)
{
	if (buf->word)
		free(buf->word);
}

t_token	*lexer(char *cmd)
{
	t_token		*token_head;
	t_token		*token_cur;
	t_buf		*buf;
	StateType	state;
	char		c;
	int			i;

	buf_init(buf);
	token_head = create_token(TOK_NUL, NULL);
	token_cur = token_head;
	i = 0;
	c = cmd[i];
	state = STA_DEFAULT;
	while (cmd[i])
	{
		if (state == STA_DEFAULT)
			lexer_default();
		else if (state == STA_IN_WORD)
			lexer_word();
		else if (state == STA_IN_SQUOTE)
			lexer_squate();
		else if (state == STA_IN_DQUOTE)
			lexer_dquate();
		else
			(state == STA_IN_VARIABLE) lexer_variable();
		i++;
		c = cmd[i];
	}
	token_cur = token_head->next;
	return (token_cur);
}


