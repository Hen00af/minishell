/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_unsigned_fd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nando <nando@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:46:27 by nando             #+#    #+#             */
/*   Updated: 2025/06/07 20:55:22 by nando            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_fprintf.h"

int	ft_put_unsigned_fd(int fd, unsigned int i)
{
	char	put_unsigned;
	int		count;

	count = 0;
	if (i >= 10)
		count += ft_put_unsigned_fd(fd, i / 10);
	put_unsigned = (i % 10) + '0';
	write(fd, &put_unsigned, 1);
	return (count + 1);
}
