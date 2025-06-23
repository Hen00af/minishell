/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shattori <shattori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 15:20:46 by nando             #+#    #+#             */
/*   Updated: 2025/06/21 14:40:09 by shattori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "builtin.h"

int	builtin_env(char **args, t_env *list_head)
{
	t_env	*current;

	current = list_head;
	if (args[1] != NULL)
		return (NG);
	while (current)
	{
		if (current->flag == 1)
		{
			if (current->value)
				ft_printf("%s=%s\n", current->key, current->value);
			else
				ft_printf("%s=\n", current->key);
		}
		current = current->next;
	}
	return (OK);
}

// int	main(int argc, char **argv, char **envp)
// {
// 	t_env	*env_head;

// 	env_head = init_env(envp);
// 	builtin_env(argv, env_head);
// }
