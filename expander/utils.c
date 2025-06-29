/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shattori <shattori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 17:19:31 by nando             #+#    #+#             */
/*   Updated: 2025/06/29 22:03:10 by shattori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

t_var	*init_var(void)
{
	t_var	*var;

	var = malloc(sizeof(t_var));
	if (!var)
		return (NULL);
	var->start = 0;
	var->len = 0;
	var->key = NULL;
	var->value = NULL;
	return (var);
}

char	*expand_all_type(char *arg, t_env *env, t_expand *ctx)
{
	arg = expand_variables(arg, env);
	arg = expand_tilda(arg, env);
	arg = expand_wild_card(arg, ctx);
	return (arg);
}

int	count_args(char **args)
{
	int	count;

	count = 0;
	while (args[count])
		count++;
	return (count);
}

void	free_args(char **argv)
{
	int	i;

	i = 0;
	if (!argv)
		return ;
	while (argv[i])
		free(argv[i++]);
	free(argv);
}

void	free_file_list(t_file_node *head)
{
	t_file_node	*tmp;

	while (head)
	{
		tmp = head->next;
		free(head->name);
		free(head);
		head = tmp;
	}
}
