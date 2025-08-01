/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nando <nando@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 15:20:46 by nando             #+#    #+#             */
/*   Updated: 2025/07/19 18:27:09 by nando            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "builtin.h"

int	builtin_env(char **args, t_env *env)
{
	t_env	*current;

	current = env;
	if (args[1] != NULL)
		return (NG);
	while (current)
	{
		if (current->flag == 1)
		{
			if (current->value)
				printf("%s=%s\n", current->key, current->value);
			else
				printf("%s=\n", current->key);
		}
		current = current->next;
	}
	return (OK);
}
