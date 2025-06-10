/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nando <nando@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 14:10:22 by nando             #+#    #+#             */
/*   Updated: 2025/01/17 18:11:31 by nando            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

static int	ft_handle_conversion(const char *format, int i, va_list args)
{
	int	count;

	count = 0;
	if (format[i] == 'c')
		count += ft_put_char(va_arg(args, int));
	else if (format[i] == 's')
		count += ft_put_str(va_arg(args, char *));
	else if (format[i] == 'd')
		count += ft_put_deci(va_arg(args, int));
	else if (format[i] == 'i')
		count += ft_put_int(va_arg(args, int));
	else if (format[i] == 'u')
		count += ft_put_unsigned(va_arg(args, unsigned int));
	else if (format[i] == '%')
		count += ft_put_per();
	else if (format[i] == 'p')
		count += ft_put_ptr((void *)va_arg(args, unsigned long));
	else if (format[i] == 'x')
		count += ft_put_hexa_lower(va_arg(args, unsigned int));
	else if (format[i] == 'X')
		count += ft_put_hexa_upper(va_arg(args, unsigned int));
	return (count);
}

int	ft_printf(const char *format, ...)
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
			count += ft_handle_conversion(format, ++i, args);
		else
			count += write(1, &format[i], 1);
		i++;
	}
	va_end(args);
	return (count);
}
