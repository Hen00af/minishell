/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_front.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shattori <shattori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 19:34:56 by shattori          #+#    #+#             */
/*   Updated: 2025/03/27 19:45:55 by shattori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	add_front(t_DList *list, int data)
{
	t_DNode	*new_node;

	new_node = create_node(data);
	if (!new_node)
		return ;
	if (list->head == NULL)
	{
		list->head = new_node;
		list->tail = new_node;
	}
	else
	{
		new_node->next = list->head;
		list->head->prev = new_node;
		list->head = new_node;
	}
	list->size++;
}
