/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_int_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nando <nando@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:45:20 by nando             #+#    #+#             */
/*   Updated: 2025/06/07 16:20:36 by nando            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_fprintf.h"

int	ft_put_int_fd(int fd, int i)
{
	char	put_int;
	int		count;

	count = 0;
	if (i == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return (11);
	}
	if (i < 0)
	{
		write(fd, "-", 1);
		i = -i;
		count++;
	}
	if (i >= 10)
		count += ft_put_int_fd(fd, i / 10);
	put_int = (i % 10) + '0';
	write(fd, &put_int, 1);
	count++;
	return (count);
}
