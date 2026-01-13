/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 16:10:49 by ranhaia-          #+#    #+#             */
/*   Updated: 2026/01/13 16:49:35 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	t_mini	mini;

	using_history();
	while (1)
	{
		mini.input = readline("> ");
		if (!mini.input)
			break ;
		if (!ft_strncmp(mini.input, "", 2))
			add_history(mini.input);
		printf("\ninput: %s\n\n", mini.input);
		mini.tokens = assign_tokens(&mini);
		print_tokens(mini.tokens);
		free_tokens(mini.tokens);
		free(mini.input);
	}
	clear_history();
	return (0);
}
