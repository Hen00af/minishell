/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_hexa_lower.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nando <nando@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:44:40 by nando             #+#    #+#             */
/*   Updated: 2025/01/17 18:11:18 by nando            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	ft_put_hexa_lower(unsigned int n)
{
	const char	hexa_lower_base[17] = "0123456789abcdef";
	int			count;

	count = 0;
	if (n == 0)
		return (write(1, "0", 1));
	if (n >= 16)
		count += ft_put_hexa_lower(n / 16);
	count += write(1, &hexa_lower_base[n % 16], 1);
	return (count);
}
