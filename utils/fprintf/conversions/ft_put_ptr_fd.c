/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_ptr_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nando <nando@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:46:01 by nando             #+#    #+#             */
/*   Updated: 2025/06/07 16:19:14 by nando            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_fprintf.h"

int	ft_put_ptr_fd(int fd, void *ptr)
{
	unsigned long long	ptr_address;
	const char			hex_base[16] = "0123456789abcdef";
	char				buf[16];
	int					i;

	ptr_address = (unsigned long long)ptr;
	if (ptr_address == 0)
	{
		write(fd, "(nil)", 5);
		return (5);
	}
	write(fd, "0x", 2);
	i = 15;
	while (ptr_address)
	{
		buf[i--] = hex_base[ptr_address % 16];
		ptr_address = ptr_address / 16;
	}
	write(fd, &buf[i + 1], 15 - i);
	return (2 + 15 - i);
}
