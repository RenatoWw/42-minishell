/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 16:10:49 by ranhaia-          #+#    #+#             */
/*   Updated: 2026/02/10 21:17:04 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// fazer:
// Handle exit codes properly throughout
// Signal handling (Ctrl+C, Ctrl+D)
// Heredoc Expander

int	g_signal;

static void	after_clean(t_mini *mini)
{
	rl_clear_history();
	free_all(mini);
	free_envp(mini->env_list);
}

int	main(int argc, char **argv, char **envp)
{
	t_mini	mini;

	initial_setup(&mini, argc, argv, envp);
	get_data(&mini);
	while (1)
	{
		setup_signals();
		set_mini_args(&mini);
		mini.prompt_str = print_dir(&mini);
		mini.input = readline(mini.prompt_str);
		if (!mini.input)
			exit_properly(&mini);
		if (mini.input[0] != '\0')
		{
			add_history(mini.input);
			get_cmd_and_execute(&mini);
		}
		else
		{
			free(mini.input);
			free(mini.prompt_str);
		}
	}
	after_clean(&mini);
	return (0);
}
