/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shattori <shattori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 19:40:05 by shattori          #+#    #+#             */
/*   Updated: 2025/04/05 01:25:17 by shattori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "../libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_pipe_fd
{
	int	pipe_fd[2];
	int	fd_in;
	int	pid;
}		t_pipe_fd;

# define FAILED -1
# define THIS_IS_NOT_FILE -1

int		make_process(int argc, char **argv, int i);
void	do_pipe(int pipe_fd[2]);
void	handle_parent(int i, int ac, char **av);
int		pipex(int ac, char **av);
int		dir_check(char *file);
int		check_file(char *infile, char *outfile);
void	check_args(int ac, char **av);
void	handle_child(t_pipe_fd pipe_fds, char *cmd, int is_last, char *outfile);
void	setup_infile(char *filename, int *fd_in);
void	setup_outfile(char *filename, int *outfile);
void	error(void);
void	error_output_fd(int input_fd, int output_fd);
void	error_input_fd(int input_fd);
void	error_pipe(t_pipe_fd pipe_fds);
void	noting_path(char **paths);

#endif // PIPEX_H
