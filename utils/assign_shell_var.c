/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_shell_var.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nando <nando@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 21:05:04 by nando             #+#    #+#             */
/*   Updated: 2025/06/07 15:20:07 by nando            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	assign_shell_var(char *var_str, t_env *list_head)
{
	int		i;
	char	**key_value;
	t_env	*node;

	i = 0;
	key_value = env_split(var_str, '=');
	node = create_env_node(key_value);
	node->flag = 0;
	while (list_head->next)
		list_head = list_head->next;
	list_head->next = node;
}


