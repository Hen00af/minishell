/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shattori <shattori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 17:27:09 by shattori          #+#    #+#             */
/*   Updated: 2024/11/09 16:17:13 by shattori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	check_sign(const char *str, long *i)
{
	int	neg;

	neg = 0;
	if (str[*i] == '-')
	{
		neg = 1;
		(*i)++;
	}
	else if (str[*i] == '+')
		(*i)++;
	return (neg);
}

int	ft_atoi(const char *str)
{
	long	i;
	long	nbr;
	int		neg;

	nbr = 0;
	i = 0;
	neg = 0;
	while (str[i] != '\0' && (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)))
		i++;
	neg = check_sign(str, &i);
	while (str[i] >= '0' && str[i] <= '9')
	{
		nbr *= 10;
		nbr += str[i] - '0';
		i++;
	}
	if (neg == 1)
		nbr *= -1;
	return (nbr);
}
