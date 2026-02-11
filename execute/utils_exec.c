/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 10:44:07 by dapinhei          #+#    #+#             */
/*   Updated: 2026/02/11 04:21:29 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_parent_fds(int *prev_fd, t_cmd *cmd, int pipefd[2])
{
	if (*prev_fd != -1)
		close(*prev_fd);
	if (cmd->next)
	{
		close(pipefd[1]);
		*prev_fd = pipefd[0];
	}
}

void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*joined;

	if (!s1 || !s2)
		return (NULL);
	joined = ft_strjoin(s1, s2);
	free(s1);
	return (joined);
}

static void	treat_signals(int status)
{
	if (WTERMSIG(status) == SIGQUIT)
		printf("Quit (core dumped)\n");
	else if (WTERMSIG(status) == SIGINT)
		printf("\n");
}

void	wait_all(t_cmd *cmd, t_mini *mini)
{
	int		status;
	t_cmd	*last;

	if (!cmd)
		return ;
	setup_exec_signals();
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
			{
				mini->exit_code = 128 + WTERMSIG(status);
				treat_signals(status);
			}
		}
		cmd = cmd->next;
	}
	setup_signals();
}
