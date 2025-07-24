/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shattori <shattori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 17:18:58 by shattori          #+#    #+#             */
/*   Updated: 2025/07/24 18:17:28 by shattori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "../minishell.h"
# include <errno.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_ast			t_ast;
typedef struct s_andor			t_andor;
typedef struct s_env			t_env;
typedef struct s_shell			t_shell;
typedef struct s_command		t_command;
typedef struct s_redirection	t_redirection;

typedef struct s_exec
{
	int							pipefd[2];
	int							prev_fd;
	pid_t						pid;
	int							in;
	int							out;
}								t_exec;

int								executor(t_andor *node, t_shell *shell);
int								exec_builtin(char **argv, t_env *env);
char							**convert_env(t_env *env);
char							*search_path(char *cmd, t_env *env);
char							*get_env_value(const char *name, t_env *env);
char							*ft_strjoin_path(char *dir, char *file);
int								env_size(t_env *env);
char							*ft_strjoin_3(char *s1, char *s2, char *s3);
char							*search_path(char *cmd, t_env *env);
int								exec_simple_command(t_command *cmd,
									t_shell *shell);
int								exec_subshell(t_command *cmd, t_shell *shell);
void							handle_redirections(t_command *cmd);
int								handle_redirections_builtin(t_command *cmd);
int								open_redirection_file_builtin(
									t_redirection *redir, char *last_tmpfile);
int								apply_redirection_builtin(int fd, int type);
int								is_builtin(const char *cmd);
int								exec_builtin(char **argv, t_env *env);
int								exec_single_builtin(t_command *cmd,
									t_exec *exec, t_shell *shell);

#endif