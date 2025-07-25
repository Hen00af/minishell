/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shattori <shattori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 09:29:46 by shattori          #+#    #+#             */
/*   Updated: 2025/07/25 09:31:21 by shattori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	safe_exit(t_shell *shell, t_andor *ast, int status)
{
	free_env_list(shell->env);
	free_andor_ast(ast);
	exit(status);
}
