/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nando <nando@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 12:54:02 by nando             #+#    #+#             */
/*   Updated: 2025/07/03 23:26:04 by nando            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H

# include "../minishell.h"
# include <stdbool.h>

typedef struct s_command	t_command;

char						*run_heredoc(const char *delimiter,
								bool need_expand, t_shell *shell);
void						process_heredoc(t_command *cmd, t_shell *shell);

#endif