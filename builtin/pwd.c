/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nando <nando@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:50:52 by nando             #+#    #+#             */
/*   Updated: 2025/07/10 18:47:51 by nando            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	builtin_pwd(char **args, t_env *env)
{
	char	*cwd;

	(void)args;
	(void)env;
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
