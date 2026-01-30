/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 13:15:11 by renato            #+#    #+#             */
/*   Updated: 2026/01/29 21:01:04 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_if_builtin(t_mini *mini)
{
	char	**cmd;
	int		i;

	cmd = mini->cmd->cmd_args;
	i = 0;
	while (cmd[i])
	{
		if (ft_strncmp(cmd[i], "export", 10) == 0)
		{
			export_builtin(mini, mini->cmd->cmd_args);
			return (1);
		}
		else if (ft_strncmp(cmd[i], "env", 10) == 0)
		{
			env_builtin(mini, mini->cmd->cmd_args);
			return (1);
		}
		else if (ft_strncmp(cmd[i], "unset", 10) == 0)
		{
			unset_builtin(mini, mini->cmd->cmd_args);
			return (1);
		}
		else if (ft_strncmp(cmd[i], "pwd", 10) == 0)
		{
			pwd_builtin(mini, mini->cmd->cmd_args);
			return (1);
		}
		else if (ft_strncmp(cmd[i], "exit", 10) == 0)
		{
			exit_builtin(mini, mini->cmd->cmd_args);
			return (1);
		}
		else if (ft_strncmp(cmd[i], "echo", 10) == 0)
		{
			echo_builtin(mini, mini->cmd->cmd_args);
			return (1);
		}
		else if (ft_strncmp(cmd[i], "cd", 10) == 0)
		{
			cd_builtin(mini, mini->cmd->cmd_args);
			return (1);
		}
		i++;
	}
	return (0);
}

void	execute_builtin(t_mini *mini)
{
	(void)mini;
}
