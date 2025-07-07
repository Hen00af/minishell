/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nando <nando@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 18:51:48 by shattori          #+#    #+#             */
/*   Updated: 2025/07/07 20:46:59 by nando            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# define ERROR -5

# include "../minishell.h"
# include <ctype.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef enum e_tokentype
{
	TOK_WORD,
	TOK_ASSIGN_WORD,
	TOK_PIPE,
	TOK_AND,
	TOK_OR,
	TOK_REDIR_IN,
	TOK_REDIR_OUT,
	TOK_REDIR_APPEND,
	TOK_HEREDOC,
	TOK_REDIR_APP,
	TOK_LPAREN,
	TOK_RPAREN,
	TOK_EOF,
	TOK_NUL
}					t_tokentype;

typedef enum e_statetype
{
	STA_DEFAULT,
	STA_IN_WORD,
	STA_IN_SQUOTE,
	STA_IN_DQUOTE,
	STA_IN_VARIABLE,
}					t_statetype;

typedef struct s_token
{
	t_tokentype		type;
	char			*text;
	struct s_token	*next;
}					t_token;

typedef struct s_buf
{
	char			*word;
	size_t			len;
	size_t			capa;
}					t_buf;

typedef struct s_lexer
{
	const char		*input;
	t_token			*head;
	t_token			*current;
	t_buf			buf;
	size_t			posi;
	size_t			move;
	t_statetype		state;
	t_statetype		prev_state;
	int				left_p_count;
	int				right_p_count;
	int				assignment_flag;
}					t_lexer;

void				buf_init(t_buf *buf);
void				buf_add(t_buf *buf, char c);
void				free_buf(t_buf *buf);
char				*buf_flush(t_buf *buf);
void				buf_add_and_assign_flag(t_lexer *ctx, char c);
void				buf_add_and_set_state(t_lexer *ctx, char c);
t_token				*create_token(t_tokentype type, char *word);
void				append_token(t_lexer *ctx, t_tokentype type, char *text);
void				append_tok_and_set_state(t_lexer *ctx, t_statetype state);
void				append_tok_and_reset_state(t_lexer *ctx, t_tokentype type);
void				free_tokens(t_token *head);
void				quate_error(t_lexer *ctx);
void				parent_error(t_lexer *ctx);
int					ft_isspace(int c);
int					is_valid_var_name(char *buf_word);
void				adjust_assign_word(t_token *head);
void				lexer_default(t_lexer *ctx, char c);
void				lexer_word(t_lexer *ctx, char c);
void				lexer_word2(t_lexer *ctx, char c);
void				lexer_squate(t_lexer *ctx, char c);
void				lexer_dquate(t_lexer *ctx, char c);
void				handle_meta(t_lexer *ctx, char c);
int					init_lexer(t_lexer *ctx, char *input);
void				run_lexer(t_lexer *ctx);
t_token				*finish_lexing(t_lexer *ctx);
t_token				*lexer(char *input);

#endif
