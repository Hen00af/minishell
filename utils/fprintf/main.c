/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nando <nando@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 16:22:37 by nando             #+#    #+#             */
/*   Updated: 2025/06/26 21:36:03 by nando            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"
#include <fcntl.h>
#include <unistd.h>

// int	main(int argc, char **argv)
//{
//	int	fd;
//	int	fd2;

//	if (argc < 2)
//	{
//		ft_fprintf(2, "Usage: %s <string>\n", argv[0]);
//		return (1);
//	}
//	fd = 1;
//	ft_fprintf(fd, "=== stdout test ===\n");
//	ft_fprintf(fd, "fd = %d : %s\n", fd, argv[1]);
//	fd = 2;
//	ft_fprintf(fd, "=== stderr test ===\n");
//	ft_fprintf(fd, "fd = %d : %s\n", fd, argv[1]);
//	fd = open("test_output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
//	if (fd == -1)
//	{
//		ft_fprintf(2, "Error: cannot open test_output.txt\n");
//		return (1);
//	}
//	ft_fprintf(fd, "=== file output test ===\n");
//	ft_fprintf(fd, "fd = %d : %s\n", fd, argv[1]);
//	ft_fprintf(1, "File output test completed! Check test_output.txt\n");
//	fd2 = open("test_output2.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
//	if (fd2 == -1)
//	{
//		ft_fprintf(2, "Error: cannot open test_output2.txt\n");
//		return (1);
//	}
//	ft_fprintf(fd2, "=== file output test ===\n");
//	ft_fprintf(fd2, "fd = %d : %s\n", fd2, argv[1]);
//	ft_fprintf(1, "File output test completed! Check test_output2.txt\n");
//	close(fd);
//	close(fd2);
//	return (0);
//}
