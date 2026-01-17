/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapinhei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 13:04:03 by dapinhei          #+#    #+#             */
/*   Updated: 2026/01/15 13:04:06 by dapinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_process(t_cmd *cmd, int *pipefd, char **envp)
{
	if (!cmd->cmd_args || !cmd->cmd_args[0])
		exit(0);

	if (cmd->fd_in != STDIN_FILENO)
	{
		dup2(cmd->fd_in, STDIN_FILENO);
		close(cmd->fd_in);
	}
	if (cmd->next)
	{
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
	}
	else if (cmd->fd_out != STDOUT_FILENO)
	{
		dup2(cmd->fd_out, STDOUT_FILENO);
		close(cmd->fd_out);
	}

	cmd->cmd_path = find_cmd_path(cmd->cmd_args[0], envp);
	if (!cmd->cmd_path)
	{
		ft_putstr_fd("minishell: command not found: ", 2);
		ft_putendl_fd(cmd->cmd_args[0], 2);
		exit(127);
	}
	execve(cmd->cmd_path, cmd->cmd_args, envp);
	perror("execve");
	exit(1);
}

void	parent_process(t_cmd *cmd, int *pipefd)
{
	if (cmd->fd_in != STDIN_FILENO)
		close(cmd->fd_in);
	if (cmd->next)
	{
		close(pipefd[1]);
		cmd->next->fd_in = pipefd[0];
	}
}

void	wait_all(t_cmd *cmd)
{
	while (cmd)
	{
		waitpid(cmd->process_pid, NULL, 0);
		cmd = cmd->next;
	}
}

void	execute_cmds(t_cmd *cmd_list, char **envp)
{
	t_cmd	*cmd;
	int		pipefd[2];

	cmd = cmd_list;
	while (cmd)
	{
		if (cmd->next)
		{
			if (pipe(pipefd) == -1)
				return (perror("pipe"));
		}
		cmd->process_pid = fork();
		if (cmd->process_pid < 0)
			return (perror("fork"));
		if (cmd->process_pid == 0)
			child_process(cmd, pipefd, envp);
		else
			parent_process(cmd, pipefd);
		cmd = cmd->next;
	}
	wait_all(cmd_list);
}