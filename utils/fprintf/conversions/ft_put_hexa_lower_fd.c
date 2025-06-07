/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_hexa_lower_fd.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nando <nando@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:44:40 by nando             #+#    #+#             */
/*   Updated: 2025/06/07 20:55:13 by nando            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_fprintf.h"

int	ft_put_hexa_lower_fd(int fd, unsigned int n)
{
	const char	hexa_lower_base[16] = "0123456789abcdef";
	int			count;

	count = 0;
	if (n == 0)
		return (write(fd, "0", 1));
	if (n >= 16)
		count += ft_put_hexa_lower_fd(fd, n / 16);
	count += write(fd, &hexa_lower_base[n % 16], 1);
	return (count);
}
