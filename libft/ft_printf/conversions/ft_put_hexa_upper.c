/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_hexa_upper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nando <nando@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:45:07 by nando             #+#    #+#             */
/*   Updated: 2025/01/17 17:38:09 by nando            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	ft_put_hexa_upper(unsigned int n)
{
	const char	hexa_upper_base[17] = "0123456789ABCDEF";
	int			count;

	count = 0;
	if (n == 0)
		return (write(1, "0", 1));
	if (n >= 16)
		count += ft_put_hexa_upper(n / 16);
	count += write(1, &hexa_upper_base[n % 16], 1);
	return (count);
}
