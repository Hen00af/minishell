/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nando <nando@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 14:30:21 by nando             #+#    #+#             */
/*   Updated: 2025/06/08 21:18:06 by nando            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

//utils.hで定義しているはず。校舎行ったときにpushする
typedef struct s_env
{
	char	*key;
	char	*value;
	int		flag;
	t_env	*next;
}			t_env;

char *replace_env(char *arg, t_env *env)
{
	
}

char *expand_string(char *arg, t_env *env)
{
	int i;

	i = 0;
	if()
	if(arg[i] == '$')
	{
		i++;
		arg[i]
	}
		
}

void	expander(t_ast *node, t_env *env)
{
	int i;

	i = 0;
	while(node->argv && node->argv[i])
	{
		node->argv[i] = expand_string(node->type, node->argv[i], env);
		i++;
	}
}