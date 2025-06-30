/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nando <nando@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 12:54:02 by nando             #+#    #+#             */
/*   Updated: 2025/06/30 21:52:39 by nando            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H

# include "../minishell.h"
# include <stdbool.h>

char	*run_heredoc(const char *delimiter, bool need_expand, t_shell *shell);
char	*process_heredoc(t_list *redir_list, t_shell *shell);

#endif