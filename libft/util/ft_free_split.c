/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nando <nando@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 16:19:51 by shattori          #+#    #+#             */
/*   Updated: 2025/08/04 18:21:43 by nando            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**free_split(char **str)
{
	int	i;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
	return (NULL);
}

// int	main(void)
// {
// 	char	**str1;
// 	char	*str2;
// 	int		i;

// 	str2 = "123*456*789";
// 	str1 = ft_split(str2, "*");
// 	if (!str1)
// 		return (1);
// 	i = 0;
// 	while (str1[i])
// 	{
// 		printf("Token %d: %s\n", i, str1[i]);
// 		i++;
// 	}
// 	free_split(str1);
// 	return (0);
// }
