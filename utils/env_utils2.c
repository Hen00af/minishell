/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nando <nando@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 19:34:22 by nando             #+#    #+#             */
/*   Updated: 2025/07/24 19:34:42 by nando            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*create_key_value(t_env *list_head, char *tmp)
{
	char	*key_value;

	if (list_head->value)
		key_value = ft_strjoin(tmp, list_head->value);
	else
		key_value = ft_strjoin(tmp, " ");
	return (key_value);
}
