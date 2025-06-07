/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shattori <shattori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 20:12:25 by shattori          #+#    #+#             */
/*   Updated: 2025/05/15 16:36:43 by shattori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipex(int ac, char **av)
{
	int	input_fd;
	int	output_fd;

	input_fd = open(av[1], O_RDONLY);
	if (input_fd == FAILED)
		error_input_fd(input_fd);
	output_fd = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (output_fd == FAILED)
		error_output_fd(input_fd, output_fd);
	if (dup2(input_fd, STDIN_FILENO) == FAILED)
	{
		close(input_fd);
		close(output_fd);
		error();
	}
	if (dup2(output_fd, STDOUT_FILENO) == FAILED)
	{
		close(input_fd);
		close(output_fd);
		error();
	}
	close(input_fd);
	close(output_fd);
	return (make_process(ac, av, 2));
}

void exevc(char *cmd)
{
	
}