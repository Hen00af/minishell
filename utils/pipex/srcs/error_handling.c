/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shattori <shattori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 20:13:02 by shattori          #+#    #+#             */
/*   Updated: 2025/03/30 22:26:08 by shattori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

#define THIS_IS_NOT_FILE -1

int	dir_check(char *file)
{
	int	is_dir;

	is_dir = access(file, F_OK);
	if (is_dir == -1)
		return (THIS_IS_NOT_FILE);
	return (0);
}

int	check_file(char *infile, char *outfile)
{
	int	infile_perm;
	int	outfile_perm;
	int	file_exist;

	infile_perm = access(infile, R_OK);
	outfile_perm = access(outfile, W_OK);
	if (outfile_perm)
	{
		file_exist = access(outfile, F_OK);
		if (file_exist)
			outfile_perm = 0;
	}
	if (!outfile_perm && !file_exist)
		outfile_perm = dir_check(outfile);
	if (!infile_perm)
		infile_perm = dir_check(infile);
	if (infile_perm || outfile_perm)
		return (1);
	return (0);
}

void	check_args(int ac, char **av)
{
	if (ac < 5)
	{
		errno = EINVAL;
		perror("Error: ");
		exit(1);
	}
	if (check_file(av[1], av[ac - 1]) != 0)
	{
		perror("Error: Can't open file");
		exit(1);
	}
}

void	error(void)
{
	perror("Error:");
	exit(1);
}
