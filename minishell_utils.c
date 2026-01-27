/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 17:45:19 by ranhaia-          #+#    #+#             */
/*   Updated: 2026/01/26 20:48:21 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_all(t_mini *mini)
{
	if (mini->tokens)
		free_tokens(mini->tokens);
	if (mini->cmd)
		free_cmds(mini->cmd);
	if (mini->input)
		free(mini->input);
}

void	restore_stdio(t_mini *mini)
{
	dup2(mini->original_stdin, STDIN_FILENO);
	dup2(mini->original_stdout, STDOUT_FILENO);
}

void	set_mini_args(t_mini *mini)
{
	mini->tokens = NULL;
	mini->cmd = NULL;
	mini->input = NULL;
}

void	validate_argc(int argc, char **argv)
{
	if (argc != 1 && argv[1])
	{
		printf("Usage: ./minishell\n");
		exit(1);
	}
}
