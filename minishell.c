/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 16:10:49 by ranhaia-          #+#    #+#             */
/*   Updated: 2026/01/09 17:08:39 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	// t_token	*token_list;
	t_mini	mini;

	mini.input = readline("> ");
	mini.tokens = assign_tokens(&mini);
	print_tokens(mini.tokens);
	// printf("%s\n", mini->tokens->value);
	// printf("%d\n", mini->tokens->type);
	// printf("%s\n", mini->input);
	free_tokens(mini.tokens);
	free(mini.input);
	// free(mini);
	// ft_strtrim();
	// token_list = create_token(line, type);
	// using_history();
	// while (1)
	// {
	// 	line = readline("> ");
	// 	if (!line)
	// 		break ;
	// 	if (!ft_strncmp(line, "", 2))
	// 		add_history(line);
	// 	printf("%s\n", line);
	// 	free(line);
	// }
	// clear_history();
	
	return (0);
}
