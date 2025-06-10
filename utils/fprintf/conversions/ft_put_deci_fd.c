/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_deci_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nando <nando@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:44:20 by nando             #+#    #+#             */
/*   Updated: 2025/06/07 16:20:18 by nando            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_fprintf.h"

int	ft_put_deci_fd(int fd, int i)
{
	char	put_deci;
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
		count += ft_put_deci_fd(fd, i / 10);
	put_deci = (i % 10) + '0';
	write(fd, &put_deci, 1);
	count++;
	return (count);
}
