/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nando <nando@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 01:06:55 by nando             #+#    #+#             */
/*   Updated: 2025/07/11 01:06:57 by nando            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer.h"

int	main(int argc, char **argv)
{
	t_token		*tokens;
	const char	*display_text;
	char		tmp[32];

	if (argc < 2)
	{
		ft_fprintf(STDERROR_INT, "Usage: %s \"input string\"\n", argv[0]);
		return (EXIT_FAILURE);
	}
	printf("Test input: %s\n", argv[1]);
	tokens = lexer(argv[1]);
	if (!tokens)
	{
		ft_fprintf(STDERROR_INT, "Lexer error.\n");
		return (EXIT_FAILURE);
	}
	ft_printf("Tokens:\n");
	for (t_token *tok = tokens; tok != NULL; tok = tok->next)
	{
		display_text = tok->text;
		if (display_text == NULL)
		{
			snprintf(tmp, sizeof(tmp), "(NULL)");
			display_text = tmp;
		}
		ft_printf("  [Type=%d]'%s'\n", tok->type, display_text);
	}
	free_tokens(tokens);
	return (EXIT_SUCCESS);
}
