/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapinhei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 06:42:33 by dapinhei          #+#    #+#             */
/*   Updated: 2026/02/08 06:42:41 by dapinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	setup_input(t_cmd *cmd, int prev_fd)
{
	if (prev_fd != -1)
	{
		if (dup2(prev_fd, STDIN_FILENO) == -1)
			perror("dup2");
		close(prev_fd);
	}
	if (cmd->fd_in != STDIN_FILENO)
	{
		if (dup2(cmd->fd_in, STDIN_FILENO) == -1)
			perror("dup2");
		close(cmd->fd_in);
	}
}

static void	setup_output(t_cmd *cmd, int pipefd[2])
{
	if (cmd->next)
	{
		close(pipefd[0]);
		if (dup2(pipefd[1], STDOUT_FILENO) == -1)
			perror("dup2");
		close(pipefd[1]);
	}
	else if (cmd->fd_out != STDOUT_FILENO)
	{
		if (dup2(cmd->fd_out, STDOUT_FILENO) == -1)
			perror("dup2");
		close(cmd->fd_out);
	}
}

static void	exec_child(t_cmd *cmd, int prev_fd,
	int pipefd[2], char **envp, t_mini *mini)
{
	setup_input(cmd, prev_fd);
	setup_output(cmd, pipefd);
	if (is_builtin(cmd->cmd_args[0]))
		exit(exec_builtin(cmd->cmd_args, mini));
	cmd->cmd_path = find_cmd_path(cmd->cmd_args[0], envp);
	if (!cmd->cmd_path)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->cmd_args[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(127);
	}
	execve(cmd->cmd_path, cmd->cmd_args, envp);
	perror("execve");
	exit(126);
}

void	execute_cmds(t_cmd *cmd, char **envp, t_mini *mini)
{
	int		pipefd[2];
	int		prev_fd;

	prev_fd = -1;
	while (cmd)
	{
		if (cmd->next && pipe(pipefd) == -1)
			return (perror("pipe"));
		cmd->process_pid = fork();
		if (cmd->process_pid == -1)
			return (perror("fork"));
		if (cmd->process_pid == 0)
			exec_child(cmd, prev_fd, pipefd, envp, mini);
		if (prev_fd != -1)
			close(prev_fd);
		if (cmd->next)
		{
			close(pipefd[1]);
			prev_fd = pipefd[0];
		}
		cmd = cmd->next;
	}
	wait_all(get_data(NULL)->cmd, mini);
}