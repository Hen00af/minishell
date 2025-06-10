/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_unsigned.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nando <nando@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:46:27 by nando             #+#    #+#             */
/*   Updated: 2025/01/17 18:11:29 by nando            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	ft_put_unsigned(unsigned int i)
{
	char	put_unsigned;
	int		count;

	count = 0;
	if (i >= 10)
		count += ft_put_unsigned(i / 10);
	put_unsigned = (i % 10) + '0';
	write(1, &put_unsigned, 1);
	return (count + 1);
}
