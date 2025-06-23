/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shattori <shattori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:50:52 by nando             #+#    #+#             */
/*   Updated: 2025/06/18 13:04:43 by shattori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	builtin_pwd(char **args, t_env *list_head)
{
	char	*cwd;

	(void)args;
	(void)list_head;
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("pwd");
		return (NG);
	}
	printf("%s\n", cwd);
	free(cwd);
	return (OK);
}
