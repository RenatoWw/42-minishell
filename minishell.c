/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 16:10:49 by ranhaia-          #+#    #+#             */
/*   Updated: 2026/01/21 19:21:02 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// fazer
// depois pesquisar alternativas para as funções using_history e clear_history
// essas duas não estão no pdf, tem a rl_clear_history, mas vou ver isso depois
// tratar aspas coladas no lexer, o echo "hello"'world' são dois tokens apenas
// terminar os testes de lexer e de parser
// expander

int	main(int argc, char **argv, char **envp)
{
	t_mini	mini;

	validate_argc(argc, argv);
	using_history();
	mini.original_stdin = dup(STDIN_FILENO);
	mini.original_stdout = dup(STDOUT_FILENO);
	while (1)
	{
		set_mini_args(&mini);
		mini.input = readline(GREEN "minishell> " RESET);
		if (!mini.input)
			break ;
		if (ft_strncmp(mini.input, "", 2))
			add_history(mini.input);
		mini.tokens = assign_tokens(&mini);
		mini.cmd = parse_tokens(mini.tokens, &mini.exit_code);
		expand_variables(&mini, envp);
		if (mini.cmd)
			execute_cmds(mini.cmd, envp);
		restore_stdio(&mini);
		free_all(&mini);
	}
	clear_history();
	return (0);
}
