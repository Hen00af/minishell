/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nando <nando@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 20:23:19 by nando             #+#    #+#             */
/*   Updated: 2025/07/10 23:43:57 by nando            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

int	search_variable(char *arg, int start)
{
	while (arg[start] && arg[start] != '$')
		start++;
	if (!arg[start])
		return (NOTHING);
	return (start);
}

bool	has_wildcard(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '*')
			return (true);
		i++;
	}
	return (false);
}

bool	is_match(const char *pattern, const char *str, int i, int j)
{
	if (pattern[i] == '\0' && str[j] == '\0')
		return (true);
	if (pattern[i] == '*')
	{
		return (is_match(pattern, str, i + 1, j) || (str[j] && is_match(pattern,
					str, i, j + 1)));
	}
	if (pattern[i] == str[j])
		return (is_match(pattern, str, i + 1, j + 1));
	return (false);
}

void	swap_name(t_file_node *current, t_file_node *next)
{
	char	*tmp;

	tmp = current->name;
	current->name = next->name;
	next->name = tmp;
}
