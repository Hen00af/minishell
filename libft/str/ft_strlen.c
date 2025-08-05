/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shattori <shattori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 14:16:30 by shattori          #+#    #+#             */
/*   Updated: 2025/08/05 15:19:43 by shattori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *in)
{
	size_t	cnt;

	if (!in)
		return (0);
	cnt = 0;
	while (in[cnt])
		cnt++;
	return (cnt);
}
