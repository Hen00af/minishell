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
	return (!strcmp(cmd, "echo") || !strcmp(cmd, "cd") || !strcmp(cmd, "pwd")
		|| !strcmp(cmd, "export") || !strcmp(cmd, "unset") || !strcmp(cmd,
			"env") || !strcmp(cmd, "exit"));
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
		exit(g_exit_status);
	}
	else
	{
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
	if (!strcmp(argv[0], "echo"))
		return (builtin_echo(argv));
	else if (!strcmp(argv[0], "cd"))
		return (builtin_cd(argv, env));
	else if (!strcmp(argv[0], "pwd"))
		return (builtin_pwd(argv, env));
	else if (!strcmp(argv[0], "export"))
		return (builtin_export(argv, &env));
	else if (!strcmp(argv[0], "unset"))
		return (builtin_unset(argv, &env));
	else if (!strcmp(argv[0], "env"))
		return (builtin_env(argv, env));
	else if (!strcmp(argv[0], "exit"))
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

int	main(int ac, char **av, char **envp)
{
	t_token	*lex;
	t_ast	*ast;
	t_andor	*linearized_ast;
	t_env	*env;

	if (ac < 2)
		return (0);
	lex = lexer(av[1]);
	ast = start_parse(lex);
	// print_ast(ast, 0);
	linearized_ast = linearizer(ast);
	env = init_env(envp);
	expander(linearized_ast, env);
	env = init_env(envp);
	executor(linearized_ast, env);
	return (0);
}
