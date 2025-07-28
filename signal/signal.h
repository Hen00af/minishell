/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nando <nando@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 14:59:47 by nando             #+#    #+#             */
/*   Updated: 2025/07/28 17:12:51 by nando            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_H
# define SIGNAL_H

# define _POSIX_C_SOURCE 200809L

# include "../minishell.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

extern volatile sig_atomic_t	g_ack_status;

void							sigint_handler(int sig_number, siginfo_t *info,
									void *context);
void							init_signal(void);

#endif