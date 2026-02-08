/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 10:44:07 by dapinhei          #+#    #+#             */
/*   Updated: 2026/01/20 12:53:18 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	wait_all(t_cmd *cmd, t_mini *mini)
{
	int		status;
	t_cmd	*last;

	if (!cmd)
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
