/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shattori <shattori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 01:07:55 by nando             #+#    #+#             */
/*   Updated: 2025/07/25 05:52:29 by shattori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include "builtin/builtin.h"
# include "executor/executor.h"
# include "expander/expander.h"
# include "get_next_line/get_next_line.h"
# include "heredoc/heredoc.h"
# include "lexer/lexer.h"
# include "libft/libft.h"
# include "linearizer/linearizer.h"
# include "parser/parser.h"
# include "signal/signal.h"
# include "utils/utils.h"
# include <readline/history.h>
# include <readline/readline.h>

# define STDERROR_INT 2
# define STDOUT_INT 1

void		expand_and_execute(t_andor *linearized_ast, t_shell *shell);
char		*run_readline(t_shell *shell);
typedef struct s_shell
{
	t_env	*env;
	int		exit_status;
	int		is_interactive;
}			t_shell;

typedef struct s_env
{
	char	*key;
	char	*value;
	int		flag;
	t_env	*next;
}			t_env;

typedef struct s_ctx
{
	t_env	*head;
	t_env	*tail;
	t_env	*node;
	char	**key_value;
}			t_ctx;

#endif
