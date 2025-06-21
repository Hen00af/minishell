/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_fank.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shattori <shattori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 14:24:41 by shattori          #+#    #+#             */
/*   Updated: 2025/06/21 19:08:55 by shattori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int			g_exit_status = 0;
// ---------- redirection handler ----------
static void	handle_redirections(t_list *redir_list)
{
	t_redirection	*redir;
	int				fd;

	while (redir_list)
	{
		redir = redir_list->content;
		fd = -1;
		if (redir->type == REDIR_IN)
			fd = open(redir->filename, O_RDONLY);
		else if (redir->type == REDIR_OUT)
			fd = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (redir->type == REDIR_APPEND)
			fd = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else if (redir->type == REDIR_HEREDOC)
		{
			// TODO: heredoc対応（後でやる）
			redir_list = redir_list->next;
			continue ;
		}
		if (fd < 0)
		{
			perror("redirection");
			exit(1);
		}
		if (redir->type == REDIR_IN)
			dup2(fd, STDIN_FILENO);
		else
			dup2(fd, STDOUT_FILENO);
		close(fd);
		redir_list = redir_list->next;
	}
}

int	is_builtin(const char *cmd)
{
	return (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "cd") || !strcmp(cmd,
			"pwd") || !ft_strcmp(cmd, "export") || !ft_strcmp(cmd, "unset")
		|| !ft_strcmp(cmd, "env") || !ft_strcmp(cmd, "exit"));
}

// ---------- command executor ----------
static void	exec_command(t_command *cmd, t_env *env)
{
	char	*path;

	if (cmd->redirections)
		handle_redirections(cmd->redirections);
	if (cmd->subshell_ast)
	{
		g_exit_status = executor(cmd->subshell_ast, env);
		exit(g_exit_status);
	}
	if (!cmd->argv || !cmd->argv[0])
		exit(0);
	if (is_builtin(cmd->argv[0]))
	{
		g_exit_status = exec_builtin(cmd->argv, env);
		// ft_printf("\nbuiltin\n");
		exit(g_exit_status);
	}
	else
	{
		// ft_printf("\nnot builtin\n");
		path = search_path(cmd->argv[0], env);
		if (!path)
		{
			perror("command not found");
			exit(127);
		}
		execve(path, cmd->argv, convert_env(env));
		perror("execve");
		exit(1);
	}
}
// run builtin
int	exec_builtin(char **argv, t_env *env)
{
	if (!argv || !argv[0])
		return (1);
	if (!ft_strcmp(argv[0], "echo"))
		return (builtin_echo(argv, env));
	else if (!ft_strcmp(argv[0], "cd"))
		return (builtin_cd(argv, env));
	else if (!ft_strcmp(argv[0], "pwd"))
		return (builtin_pwd(argv, env));
	else if (!ft_strcmp(argv[0], "export"))
		return (builtin_export(argv, &env));
	else if (!ft_strcmp(argv[0], "unset"))
		return (builtin_unset(argv, &env));
	else if (!ft_strcmp(argv[0], "env"))
		return (builtin_env(argv, env));
	else if (!ft_strcmp(argv[0], "exit"))
		return (builtin_exit(argv));
	return (1);
}

// ---------- pipeline executor ----------
static int	exec_pipeline(t_pipeline *pipeline, t_env *env)
{
	int			prev_fd;
	int			pipefd[2];
	pid_t		pid;
	t_list		*cmd_list;
	int			status;
	t_command	*cmd;

	prev_fd = -1;
	cmd_list = pipeline->commands;
	status = 0;
	while (cmd_list)
	{
		cmd = cmd_list->content;
		if (cmd_list->next && pipe(pipefd) == -1)
		{
			perror("pipe");
			return (1);
		}
		pid = fork();
		if (pid == 0)
		{
			if (prev_fd != -1)
			{
				dup2(prev_fd, STDIN_FILENO);
				close(prev_fd);
			}
			if (cmd_list->next)
			{
				close(pipefd[0]);
				dup2(pipefd[1], STDOUT_FILENO);
				close(pipefd[1]);
			}
			exec_command(cmd, env);
		}
		else if (pid < 0)
		{
			perror("fork");
			return (1);
		}
		if (prev_fd != -1)
			close(prev_fd);
		if (cmd_list->next)
		{
			close(pipefd[1]);
			prev_fd = pipefd[0];
		}
		cmd_list = cmd_list->next;
	}
	while (wait(&status) > 0)
		;
	return (WEXITSTATUS(status));
}

// ---------- and/or executor ----------
static int	exec_andor(t_andor *node, t_env *env)
{
	int	left_status;

	left_status = executor(node->left, env);
	if ((node->type == ANDOR_AND && left_status == 0) || (node->type == ANDOR_OR
			&& left_status != 0))
		return (executor(node->right, env));
	return (left_status);
}

// ---------- main dispatcher ----------
int	executor(t_andor *node, t_env *env)
{
	if (!node)
		return (0);
	if (node->type == ANDOR_AND || node->type == ANDOR_OR)
		return (exec_andor(node, env));
	if (node->type == ANDOR_PIPELINE)
		return (exec_pipeline(node->pipeline, env));
	return (1);
}

// 検索して最初に見つけた実行可能ファイルのパスを返す
char	*search_path(char *cmd, t_env *env)
{
	char	**paths;
	char	*path_var;
	char	*full_path;
	int		i;

	if (ft_strchr(cmd, '/')) // 絶対or相対パスならそのまま使う
		return (ft_strdup(cmd));
	path_var = get_env_value("PATH", env);
	if (!path_var)
		return (NULL);
	paths = ft_split(path_var, ":");
	i = 0;
	while (paths[i])
	{
		full_path = ft_strjoin_path(paths[i], cmd); // "/"を挿入する版のstrjoin
		if (access(full_path, X_OK) == 0)
			return (free_split(paths), full_path);
		free(full_path);
		i++;
	}
	free_split(paths);
	return (NULL);
}

char	**convert_env(t_env *env)
{
	char	**envp;
	t_env	*cur;
	int		i;
	int		size;

	size = env_size(env);
	envp = malloc(sizeof(char *) * (size + 1));
	if (!envp)
		return (NULL);
	i = 0;
	cur = env;
	while (cur)
	{
		envp[i] = ft_strjoin_3(cur->key, "=", cur->value);
		i++;
		cur = cur->next;
	}
	envp[i] = NULL;
	return (envp);
}

char	*get_env_value(const char *name, t_env *env)
{
	while (env)
	{
		if (ft_strcmp(env->key, name) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

char	*ft_strjoin_path(char *dir, char *file)
{
	char	*tmp;
	char	*res;

	tmp = ft_strjoin(dir, "/");
	res = ft_strjoin(tmp, file);
	free(tmp);
	return (res);
}

int	env_size(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

char	*ft_strjoin_3(char *s1, char *s2, char *s3)
{
	char	*tmp;
	char	*res;

	tmp = ft_strjoin(s1, s2);
	res = ft_strjoin(tmp, s3);
	free(tmp);
	return (res);
}

int	main(int ac, char **av, char **envp)
{
	t_token	*lex;
	t_ast	*ast;
	t_andor	*linearized_ast;
	t_env	*env;
	char	*cmd;
	t_token	*token_head;

	env = init_env(envp);
	while (1)
	{
		cmd = readline("minishell# ");
		add_history(cmd);
		lex = lexer(cmd);
		ast = start_parse(lex);
		if (!ast)
			continue ;
		linearized_ast = linearizer(ast);
		expander(linearized_ast, env);
		executor(linearized_ast, env);
		free(cmd);
	}
	return (0);
}
