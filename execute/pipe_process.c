/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 13:04:03 by dapinhei          #+#    #+#             */
/*   Updated: 2026/01/26 18:10:12 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// printf(
// "DEBUG CHILD [%s] fd_in=%d fd_out=%d\n",
// cmd->cmd_args[0],
// cmd->fd_in,
// cmd->fd_out
// );

void	child_process(t_cmd *cmd, int *pipefd, char **envp)
{
	if (!cmd || !cmd->cmd_args || !cmd->cmd_args[0])
		exit(0);
	if (cmd->fd_in != STDIN_FILENO)
	{
		if (dup2(cmd->fd_in, STDIN_FILENO) < 0)
			perror("dup2 stdin");
		close(cmd->fd_in);
	}
	if (cmd->next)
	{
		if (dup2(pipefd[1], STDOUT_FILENO) < 0)
			perror("dup2 pipe");
		close(pipefd[0]);
		close(pipefd[1]);
	}
	else if (cmd->fd_out != STDOUT_FILENO)
	{
		if (dup2(cmd->fd_out, STDOUT_FILENO) < 0)
			perror("dup2 strout");
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
	if (!cmd)
		return ;
	if (cmd->next)
	{
		close(pipefd[1]);
		cmd->next->fd_in = pipefd[0];
	}
}

void	wait_all(t_cmd *cmd, t_mini *mini)
{
	int		status;
	t_cmd	*last;

	if (!cmd || !mini)
		return ;
	last = cmd;
	while (last->next)
		last = last->next;
	while (cmd)
	{
		waitpid(cmd->process_pid, &status, 0);
		if (cmd == last)
		{
			if (WIFEXITED(status))
				mini->exit_code = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				mini->exit_code = 128 + WTERMSIG(status);
		}
		cmd = cmd->next;
	}
}

void	execute_cmds(t_cmd *cmd_list, char **envp, t_mini *mini)
{
	t_cmd	*cmd;
	int		pipefd[2];
	int		prev_fd;

	cmd = cmd_list;
	prev_fd = -1;
	while (cmd)
	{
		pipefd[0] = -1;
		pipefd[1] = -1;
		if (prev_fd != -1)
			cmd->fd_in = prev_fd;
		if (cmd->next)
		{
			if (pipe(pipefd) < 0)
			{
				perror("pipe");
				return ;
			}
		}
		cmd->process_pid = fork();
		if (cmd->process_pid < 0)
		{
			perror("fork");
			return ;
		}
		if (cmd->process_pid == 0)
			child_process(cmd, pipefd, envp);
		else
		{
			if (prev_fd != -1)
				close(prev_fd);
			if (cmd->next)
			{
				close(pipefd[1]);
				prev_fd = pipefd[0];
			}
			else
				prev_fd = -1;
		}
		cmd = cmd->next;
	}
	wait_all(cmd_list, mini);
}
