/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nando <nando@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 15:28:33 by nando             #+#    #+#             */
/*   Updated: 2025/07/04 20:11:53 by nando            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "builtin.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static int	is_numeric(const char *str)
{
	int	i;

	i = 0;
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	builtin_exit(char **args)
{
	int	status;
	int	count;

	count = count_args(args);
	printf("exit\n");
	if (count > 2)
	{
		fprintf(stderr, "minishell: exit: too many arguments\n");
		return (1);
	}
	else if (count == 1)
		exit(0);
	if (!is_numeric(args[1]))
	{
		fprintf(stderr, "minishell: exit: %s: numeric argument required\n",
			args[1]);
		exit(255);
	}
	status = ft_atoi(args[1]) % 256;
	if (status < 0)
		status += 256;
	exit(status);
}
