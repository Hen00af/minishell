/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nando <nando@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 22:34:59 by nando             #+#    #+#             */
/*   Updated: 2025/06/30 19:00:05 by nando            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"

static char	*generate_tmpfile_path(void)
{
	static int	g_heredoc_count = 0;
	char		*heredoc_count_str;
	char		*path;
	char		*dest;
	size_t		idx;

	heredoc_count_str = ft_itoa(g_heredoc_count++);
	if (!heredoc_count_str || !(path = malloc(ft_strlen("/tmp/heredoc_")
				+ ft_strlen(heredoc_count_str) + ft_strlen(".tmp") + 1)))
	{
		free(heredoc_count_str);
		return (NULL);
	}
	dest = path;
	idx = 0;
	while ("/tmp/heredoc_"[idx])
		*dest++ = "/tmp/heredoc_"[idx++];
	idx = 0;
	while (heredoc_count_str[idx])
		*dest++ = heredoc_count_str[idx++];
	idx = 0;
	while (".tmp"[idx])
		*dest++ = ".tmp"[idx++];
	*dest = '\0';
	free(heredoc_count_str);
	return (path);
}

char	*run_heredoc(const char *delimiter, bool need_expand, t_shell *shell)
{
	char	*path;
	int		fd;
	char	*line;

	g_ack_status = 0;
	while (1)
	{
		path = generate_tmpfile_path();
		if (!path)
			return (NULL);
		fd = open(path, O_CREAT | O_EXCL | O_WRONLY, 0600);
		if (fd >= 0)
			break ;
		free(path);
	}
	while (1)
	{
		line = readline("> ");
		if (g_ack_status == 1)
		{
			free(line);
			unlink(path);
			free(path);
			path = NULL;
			break ;
		}
		if (!line)
			break ;
		if (strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		if (need_expand)
			line = expand_variables(line, shell);
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
	return (path);
}

// void	process_heredoc(t_command *cmd, t_env *env)
// {
// 	t_list			*node;
// 	t_redirection	*redir;
// 	char			*tmpfile;

// 	if (!cmd || !cmd->redirections)
// 		return ;
// 	node = cmd->redirections;
// 	while (node)
// 	{
// 		redir = (t_redirection *)node->content;
// 		if (redir->type == REDIR_HEREDOC)
// 		{
// 			tmpfile = run_heredoc(redir->filename, redir->need_expand, env);
// 			free(redir->filename);
// 			redir->filename = tmpfile;
// 		}
// 		node = node->next;
// 	}
// }

// void	handle_heredoc(t_andor *node, t_env *env)
// {
// 	t_list		*cmds;
// 	t_command	*cmd;

// 	if (!node)
// 		return ;
// 	if (node->type == ANDOR_PIPELINE)
// 	{
// 		cmds = node->pipeline->commands;
// 		while (cmds)
// 		{
// 			cmd = (t_command *)cmds->content;
// 			process_heredoc(cmd, env);
// 			cmds = cmds->next;
// 		}
// 	}
// 	else
// 	{
// 		handle_heredoc(node->left, env);
// 		handle_heredoc(node->right, env);
// 	}
// }

// #include <fcntl.h>
// #include <readline/readline.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <unistd.h>

// int	main(int argc, char **argv, char **envp)
// {
// 	char	*path;
// 	int		fd;
// 	char	buf[1024];
// 	ssize_t	n;
// 	t_env	*env;

// 	env = malloc(sizeof(t_env));
// 	env = init_env(envp);
// 	// ■ テスト１: need_expand = false
// 	printf("=== heredoc without expansion (delimiter: END) ===\n");
// 	path = run_heredoc("END", false, env);
// 	if (!path)
// 	{
// 		fprintf(stderr, "run_heredoc failed\n");
// 		return (1);
// 	}
// 	printf("→ saved to %s\n", path);
// 	fd = open(path, O_RDONLY);
// 	if (fd < 0)
// 	{
// 		perror("open");
// 		free(path);
// 		return (1);
// 	}
// 	printf("--- file content ---\n");
// 	while ((n = read(fd, buf, sizeof(buf) - 1)) > 0)
// 	{
// 		buf[n] = '\0';
// 		printf("%s", buf);
// 	}
// 	printf("--- end content ---\n");
// 	close(fd);
// 	unlink(path);
// 	free(path);
// 	// ■ テスト２: need_expand = true
// 	printf("\n=== heredoc with expansion (delimiter: EXP) ===\n");
// 	path = run_heredoc("EXP", true, env);
// 	if (!path)
// 	{
// 		fprintf(stderr, "run_heredoc failed\n");
// 		return (1);
// 	}
// 	printf("→ saved to %s\n", path);
// 	fd = open(path, O_RDONLY);
// 	if (fd < 0)
// 	{
// 		perror("open");
// 		free(path);
// 		return (1);
// 	}
// 	printf("--- file content ---\n");
// 	while ((n = read(fd, buf, sizeof(buf) - 1)) > 0)
// 	{
// 		buf[n] = '\0';
// 		printf("%s", buf);
// 	}
// 	printf("--- end content ---\n");
// 	close(fd);
// 	unlink(path);
// 	free(path);
// 	return (0);
// }
