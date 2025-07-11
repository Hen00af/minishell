/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nando <nando@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 21:05:26 by nando             #+#    #+#             */
/*   Updated: 2025/07/10 18:02:15 by nando            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	is_option(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '-')
	{
		i++;
		while (arg[i] == 'n')
			i++;
		if (arg[i] == '\0')
			return (1);
	}
	return (0);
}

void	n_flag_or_print(t_echo *e, char *arg)
{
	if (e->print_flag == 0 && is_option(arg))
		e->option_flag = 1;
	else
	{
		e->print_flag = 1;
		if (e->i + 1 != e->count)
			printf("%s ", arg);
		else
			printf("%s", arg);
	}
	e->i++;
}

int	builtin_echo(char **args, t_env *env)
{
	t_echo	e;
	int		i;

	i = 0;
	(void)env;
	e.option_flag = 0;
	e.print_flag = 0;
	e.count = count_args(args);
	if (args[1] == NULL)
	{
		printf("\n");
		return (OK);
	}
	e.i = 1;
	while (e.i < e.count)
		n_flag_or_print(&e, args[e.i]);
	if (e.option_flag == 0)
		printf("\n");
	return (OK);
}
