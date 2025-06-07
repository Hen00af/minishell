/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nando <nando@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 14:10:22 by nando             #+#    #+#             */
/*   Updated: 2025/06/07 20:55:03 by nando            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"

static int	ft_fprintf_handle_conversion(int fd, const char *format, int i,
		va_list args)
{
	int	count;

	count = 0;
	if (format[i] == 'c')
		count += ft_put_char_fd(fd, va_arg(args, int));
	else if (format[i] == 's')
		count += ft_put_str_fd(fd, va_arg(args, char *));
	else if (format[i] == 'd')
		count += ft_put_deci_fd(fd, va_arg(args, int));
	else if (format[i] == 'i')
		count += ft_put_int_fd(fd, va_arg(args, int));
	else if (format[i] == 'u')
		count += ft_put_unsigned_fd(fd, va_arg(args, unsigned int));
	else if (format[i] == '%')
		count += ft_put_per_fd(fd);
	else if (format[i] == 'p')
		count += ft_put_ptr_fd(fd, (void *)va_arg(args, unsigned long));
	else if (format[i] == 'x')
		count += ft_put_hexa_lower_fd(fd, va_arg(args, unsigned int));
	else if (format[i] == 'X')
		count += ft_put_hexa_upper_fd(fd, va_arg(args, unsigned int));
	else
		count += write(fd, &format[i - 1], 1);
	return (count);
}

int	ft_fprintf(int fd, const char *format, ...)
{
	va_list	args;
	int		i;
	int		count;

	i = 0;
	count = 0;
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%')
			count += ft_fprintf_handle_conversion(fd, format, ++i, args);
		else
			count += write(fd, &format[i], 1);
		i++;
	}
	va_end(args);
	return (count);
}
