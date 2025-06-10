/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nando <nando@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 14:10:25 by nando             #+#    #+#             */
/*   Updated: 2025/01/17 17:13:54 by nando            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

int		ft_put_char(char c);
int		ft_put_str(char *str);
int		ft_put_deci(int i);
int		ft_put_int(int i);
int		ft_put_per(void);
int		ft_put_unsigned(unsigned int i);
int		ft_put_ptr(void *ptr);
int		ft_put_hexa_lower(unsigned int n);
int		ft_put_hexa_upper(unsigned int n);
int		ft_printf(const char *format, ...);
size_t	ft_strlen(const char *s);

#endif
