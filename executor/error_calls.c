/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_calls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shattori <shattori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 20:06:43 by shattori          #+#    #+#             */
/*   Updated: 2025/05/15 16:33:21 by shattori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_pipe(t_pipe_fd pipe_fds)
{
	close(pipe_fds.fd_in);
	perror("pipe failed");
	exit(1);
}

void	error_input_fd(int input_fd)
{
	perror("Error opening input file");
	close(input_fd);
	exit(1);
}

void	error_output_fd(int input_fd, int output_fd)
{
	perror("Error opening output file");
	close(input_fd);
	close(output_fd);
	exit(1);
}

void	noting_path(char **paths)
{
	int	i;

	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
	perror("Command not found");
}
