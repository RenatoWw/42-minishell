/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 16:10:49 by ranhaia-          #+#    #+#             */
/*   Updated: 2026/01/29 18:31:14 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// fazer
// depois pesquisar alternativas para as funções using_history e clear_history
// essas duas não estão no pdf, tem a rl_clear_history, mas vou ver isso depois
// expander no heredoc

// Implement remaining builtins (echo, cd)
// Handle exit codes properly throughout
// Test all pipe and redirection combinations
// Built-ins not working with pipes
// Signal handling (Ctrl+C, Ctrl+D)
// Fix heredoc memory leak
// Pass the copied envp to the executor

void	executioner(t_mini *mini, char **envp)
{
	if (mini->cmd)
	{
		expand_variables(mini);
		if (check_if_builtin(mini) == 1)
			execute_builtin(mini);
		else if (mini->cmd)
			execute_cmds(mini->cmd, envp, mini);
	}
}

void	initial_setup(t_mini *mini, int argc, char **argv, char **envp)
{
	validate_argc(argc, argv);
	mini->original_stdin = dup(STDIN_FILENO);
	mini->original_stdout = dup(STDOUT_FILENO);
	mini->exit_code = 0;
	copy_envp(mini, envp);
}

int	main(int argc, char **argv, char **envp)
{
	t_mini	mini;

	initial_setup(&mini, argc, argv, envp);
	using_history();
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
		executioner(&mini, envp);
		restore_stdio(&mini);
		free_all(&mini);
	}
	clear_history();
	free_all(&mini);
	free_envp(mini.env_list);
	return (0);
}
