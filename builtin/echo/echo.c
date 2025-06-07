/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nando <nando@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 21:05:26 by nando             #+#    #+#             */
/*   Updated: 2025/06/07 20:44:49 by nando            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../builtin.h"

static int	count_args(char **args)
{
	int	count;

	count = 0;
	while (args[count])
		count++;
	return (count);
}

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

int	builtin_echo(char **args, t_env *list_head)
{
	t_echo	*e;

	(void)list_head;
	e = malloc(sizeof(e));
	e->option_flag = 0;
	e->print_flag = 0;
	e->count = count_args(args);
	if (e->count == 1)
	{
		printf("\n");
		return (OK);
	}
	e->i = 1;
	while (e->i < e->count)
		n_flag_or_print(e, args[e->i]);
	if (e->option_flag == 0)
		printf("\n");
	return (OK);
}

// int	main(int argc, char **argv)
// {
// 	(void)argc;
// 	builtin_echo(argv);
// 	return (0);
// }
