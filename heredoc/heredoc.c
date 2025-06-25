/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nando <nando@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 22:34:59 by nando             #+#    #+#             */
/*   Updated: 2025/06/25 21:13:59 by nando            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "heredoc.h"

//typedef struct s_ast		t_ast;
//typedef enum e_node_type	t_node_type;

//typedef enum e_redir_type
//{
//	REDIR_IN,
//	REDIR_OUT,
//	REDIR_APPEND,
//	REDIR_HEREDOC
//}							t_redir_type;

//typedef struct s_redirection
//{
//	t_redir_type			type;
//	char					*filename;
//}							t_redirection;

//typedef struct s_command
//{
//	char					**argv;
//	t_list					*redirections;
//	struct s_andor			*subshell_ast;
//}							t_command;

//typedef struct s_pipeline
//{
//	t_list					*commands;
//}							t_pipeline;

//typedef enum e_andor_type
//{
//	ANDOR_PIPELINE,
//	ANDOR_AND,
//	ANDOR_OR
//}							t_andor_type;

//typedef struct s_andor
//{
//	t_andor_type			type;
//	union
//	{
//		struct
//		{
//			struct s_andor	*left;
//			struct s_andor	*right;
//		};
//		t_pipeline			*pipeline;
//	};
//}							t_andor;

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

char	*run_heredoc(const char *delimiter)
{
	char	*path;
	int		fd;
	char	*line;

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
		if (!line)
			break ;
		if (strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
	return (path);
}

void	process_heredoc(t_command *cmd)
{
	t_list			*node;
	t_redirection	*redir;
	char			*tmpfile;

	if (!cmd || !cmd->redirections)
		return ;
	node = cmd->redirections;
	while (node)
	{
		redir = (t_redirection *)node->content;
		if (redir->type == REDIR_HEREDOC)
		{
			tmpfile = run_heredoc(redir->filename);
			free(redir->filename);
			redir->filename = tmpfile;
		}
		node = node->next;
	}
}

void	handle_heredoc(t_andor *node)
{
	t_list		*cmds;
	t_command	*cmd;

	if (!node)
		return ;
	if (node->type == ANDOR_PIPELINE)
	{
		cmds = node->pipeline->commands;
		while (cmds)
		{
			cmd = (t_command *)cmds->content;
			process_heredoc(cmd);
			cmds = cmds->next;
		}
	}
	else
	{
		handle_heredoc(node->left);
		handle_heredoc(node->right);
	}
}

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	main(void)
{
	char	*path;
	int		fd;
	char	buf[1024];
	ssize_t	n;

	path = run_heredoc("END");
	if (!path)
	{
		fprintf(stderr, "run_heredoc failed\n");
		return (1);
	}
	printf("→ heredoc saved to: %s\n", path);
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		perror("open");
		free(path);
		return (1);
	}
	printf("---- file content ----\n");
	while ((n = read(fd, buf, sizeof(buf) - 1)) > 0)
	{
		buf[n] = '\0';
		printf("%s", buf);
	}
	printf("---- end content ----\n");
	close(fd);
	if (unlink(path) < 0)
		perror("unlink");
	free(path);
	return (0);
}
