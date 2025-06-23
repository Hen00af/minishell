/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shattori <shattori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 14:10:25 by nando             #+#    #+#             */
/*   Updated: 2025/06/22 19:17:35 by shattori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FPRINTF_H
# define FT_FPRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

int	ft_put_char_fd(int fd, char c);
int	ft_put_str_fd(int fd, char *str);
int	ft_put_deci_fd(int fd, int i);
int	ft_put_int_fd(int fd, int i);
int	ft_put_per_fd(int fd);
int	ft_put_unsigned_fd(int fd, unsigned int i);
int	ft_put_ptr_fd(int fd, void *ptr);
int	ft_put_hexa_lower_fd(int fd, unsigned int n);
int	ft_put_hexa_upper_fd(int fd, unsigned int n);
int	ft_fprintf(int fd, const char *format, ...);

#endif
