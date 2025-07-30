/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shattori <shattori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 12:54:02 by nando             #+#    #+#             */
/*   Updated: 2025/07/30 10:22:21 by shattori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H

//# include "../linearizer/linearizer.h"
# include "../minishell.h"
# include <stdbool.h>

typedef struct s_command		t_command;
typedef struct s_redirection	t_redirection;

typedef struct s_tmp
{
	char						*file;
	int							flag;
}								t_tmp;

typedef struct s_heredoc_file
{
	int							fd;
	char						*path;
}								t_heredoc_file;

char							*append_str(char *dst, const char *src);
char							*build_tmp_path(const char *count_str);
char							*generate_tmpfile_path(void);
int								is_include_quote(char *delimiter);
void							write_heredoc_lines(int fd,
									char *clean_delimiter, int need_expand,
									t_shell *shell);
void							child_heredoc_process(int fd, char *delimiter,
									int expand, t_shell *shell);
char							*handle_fork_error(int fd, char *delimiter,
									char *path);
t_heredoc_file					open_and_prepare_file(char *delimiter,
									char **clean_delimiter);
int								open_heredoc_file(char **path);
char							*run_heredoc(char *delimiter, t_shell *shell);
int								handle_heredoc(t_tmp *ctx, t_command *cmd,
									t_redirection *redir, t_shell *shell);
void							process_heredoc(t_command *cmd, t_shell *shell);
t_command						*handle_redir_node(t_ast *ast, t_shell *shell);
char							*finalize_heredoc(pid_t pid, char *path,
									struct sigaction *old);
#endif