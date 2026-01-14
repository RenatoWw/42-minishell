/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 16:10:49 by ranhaia-          #+#    #+#             */
/*   Updated: 2026/01/14 18:25:16 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// depois pesquisar alternativas para as funções using_history e clear_history
// essas duas não estão no pdf, tem a rl_clear_history, mas vou ver isso depois

int	main(void)
{
	t_mini	mini;

	using_history();
	while (1)
	{
		mini.input = readline(GREEN "minishell> " RESET);
		// mini.input = ft_strdup("ls -la | echo -n 5 oi");
		if (!mini.input)
			// return (1);
			break ;
		if (ft_strncmp(mini.input, "", 2))
			add_history(mini.input);
		printf("input: %s\n", mini.input);
		mini.tokens = assign_tokens(&mini);
		// print_tokens(mini.tokens);
		mini.cmd = parse_tokens(mini.tokens, &mini.exit_code);
		free_tokens(mini.tokens);
		free(mini.input);
	}
	clear_history();
	return (0);
}
