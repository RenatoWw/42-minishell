/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_single_builtin.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapinhei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 06:43:43 by dapinhei          #+#    #+#             */
/*   Updated: 2026/02/08 06:43:47 by dapinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	execute_single_builtin(t_mini *mini)
{
	int	stdin_copy;
	int	stdout_copy;
	int	status;

	stdin_copy = dup(STDIN_FILENO);
	stdout_copy = dup(STDOUT_FILENO);
	if (mini->cmd->fd_in != STDIN_FILENO)
		dup2(mini->cmd->fd_in, STDIN_FILENO);
	if (mini->cmd->fd_out != STDOUT_FILENO)
		dup2(mini->cmd->fd_out, STDOUT_FILENO);
	status = exec_builtin(mini->cmd->cmd_args, mini);
	dup2(stdin_copy, STDIN_FILENO);
	dup2(stdout_copy, STDOUT_FILENO);
	close(stdin_copy);
	close(stdout_copy);
	return (status);
}
