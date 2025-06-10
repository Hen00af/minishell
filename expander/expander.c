/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nando <nando@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 14:30:21 by nando             #+#    #+#             */
/*   Updated: 2025/06/10 11:41:47 by nando            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include <dirent.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_ast
{
	t_node_type		type;
	QuoteType		q_type;
	char			**argv;
	struct s_ast	*left;
	struct s_ast	*right;
	char			*filename;
}					t_ast;

typedef struct s_env
{
	char			*key;
	char			*value;
	int				flag;
	t_env			*next;
}					t_env;

char	*expand_variables(char *arg, t_env *env_node)
{
	int		i;
	int		j;
	int		flag;
	char	*var;
	char	*replace_var;
	size_t	var_len;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '$' && arg[i + 1] == '{')
		{
			j = i;
			while (arg[j] != '}')
				j++;
			var_len = j - (i + 2);
			var = malloc(sizeof(char) * (var_len + 1));
			if (!var)
				return (NULL);
			ft_strlcpy(var, &arg[i + 2], var_len + 1);
		}
		else if (arg[i] == '$' && arg[i + 1] != '{')
			var = ft_strdup(arg[i + 1]);
		var_len = ft_strlen(var);
		while (env_node->next)
		{
			if (ft_strncmp(var, env_node->key, var_len) == 0)
			{
				var = ft_strdup(env_node->value);
			}
			env_node = env_node->next;
		}
	}
}

char	*expand_tilda(char *arg, t_env *env)
{
}

char	*expand_wild_card(char *arg, t_env *env)
{
}

char	*expand_string(t_ast *node, char *arg, t_env *env)
{
	DIR	*dir;
	int	i;

	i = 0;
	printf("default arg = %s\n", arg);
	if (node->q_type == QUOTE_SINGLE)
	{
		// printf("[single quote]no expanded arg = %s\n", arg);
		return (arg);
	}
	else if (node->q_type == QUOTE_DOUBLE)
	{
		arg = expand_variables(arg, env);
		// printf("[double quote]expanded variables arg = %s\n", arg);
		return (arg);
	}
	arg = expand_variables(arg, env);
	// printf("[none quote]expanded variables arg = %s\n", arg);
	arg = expand_tilda(arg, env);
	// printf("[none quote]expanded tilda arg = %s\n", arg);
	arg = expand_wild_card(arg, env);
	// printf("[none quote]expanded wild_card arg = %s\n", arg);
	return (arg);
}

void	expander(t_ast *node, t_env *env)
{
	int i;

	i = 0;
	while (node->argv && node->argv[i])
	{
		node->argv[i] = expand_string(node, node->argv[i], env);
		i++;
	}
}