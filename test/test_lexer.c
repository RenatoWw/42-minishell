/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 16:56:48 by ranhaia-          #+#    #+#             */
/*   Updated: 2026/01/20 18:18:00 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// int	test_syntax(t_mini *mini)
// {	
// }

void	test_lexer(t_mini *mini)
{
	int		i;
	char 	*tests_lexer[] = {
		"ls     -la\t\t-h",				// 1. Espaços e Tabs
		"echo \"hello\"'world'",		// 2. Aspas Coladas
		"ls \"\"",						// 3. Aspas Vazias
		"| |",							// 4. Sintaxe Inválida (Erro)
		"> file ls -l",					// 5. Ordem dos Redirecionamentos
		"ls -l | grep a",			// Extra: Pipe + Redir no início
		NULL
	};

	i = 0;
	printf("\n============LEXER============\n");
	while (tests_lexer[i])
	{
		mini->input = tests_lexer[i];
		printf("Comando: %s\n=====\n", mini->input);
		mini->tokens = assign_tokens(mini);
		print_tokens(mini->tokens);
		printf("=====\n");
		i++;
	}	
	printf("============LEXER============\n\n");
}
