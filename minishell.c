/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 16:10:49 by ranhaia-          #+#    #+#             */
/*   Updated: 2026/01/31 05:23:13 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// fazer
// depois pesquisar alternativas para as funções using_history e clear_history
// essas duas não estão no pdf, tem a rl_clear_history, mas vou ver isso depois
// expander no heredoc

// Handle exit codes properly throughout
// Test all pipe and redirection combinations
// Built-ins not working with pipes
// Signal handling (Ctrl+C, Ctrl+D)
// Pass the copied envp to the executor
// Heredoc Expander

int	g_signal;

void	get_cmd_and_execute(t_mini *mini, char **envp)
{
	mini->tokens = assign_tokens(mini);
	mini->cmd = parse_tokens(mini->tokens, &mini->exit_code);
	if (mini->cmd)
	{
		expand_variables(mini);
		if (check_if_builtin(mini) == 1)
			execute_builtin(mini);
		else if (mini->cmd)
			execute_cmds(mini->cmd, envp, mini);
	}
	restore_stdio(mini);
	free_all(mini);
}

void	exit_properly(t_mini *mini)
{
	printf("exit\n");
	free_all(mini);
	free_envp(mini->env_list);
	exit(0);
}

int	main(int argc, char **argv, char **envp)
{
	t_mini	mini;

	initial_setup(&mini, argc, argv, envp);
	get_data(&mini);
	using_history();
	while (1)
	{
		setup_signals();
		set_mini_args(&mini);
		mini.prompt_str = print_dir(&mini);
		mini.input = readline(mini.prompt_str);
		if (!mini.input)
			exit_properly(&mini);
		if (ft_strncmp(mini.input, "", 2))
			add_history(mini.input);
		get_cmd_and_execute(&mini, envp);
	}
	clear_history();
	free_all(&mini);
	free_envp(mini.env_list);
	return (0);
}
