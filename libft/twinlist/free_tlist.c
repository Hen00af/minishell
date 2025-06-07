/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tlist.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shattori <shattori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 19:34:21 by shattori          #+#    #+#             */
/*   Updated: 2025/03/27 19:45:14 by shattori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_list(t_DList *list)
{
	t_DNode	*current;
	t_DNode	*next;

	current = list->head;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
	free(list);
}
