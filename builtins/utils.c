/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 13:15:11 by renato            #+#    #+#             */
/*   Updated: 2026/01/25 13:29:02 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Your shell must implement the following built-in commands:
// ◦ echo with option -n
// ◦ cd with only a relative or absolute path
// ◦ pwd with no options
// ◦ export with no options
// ◦ unset with no options
// ◦ env with no options or arguments
// ◦ exit with no options

void	env_builtin(t_mini *mini)
{
	t_env	*temp;

	temp = mini->env_list;
	if (!temp)
		return ;
	while (temp != NULL)
	{
		printf("%s=%s\n", temp->key, temp->value);
		temp = temp->next;
	}
}

int	check_if_builtin(t_mini *mini)
{
	char	*cmd;

	cmd = mini->cmd->cmd_args[0];
	if (ft_strncmp(cmd, "export", 10) == 0)
	{
		printf("cmd: %s\n", cmd);
		return (1);
	}
	else if (ft_strncmp(cmd, "env", 10) == 0)
	{
		env_builtin(mini);
		return (1);
	}
	return (0);
}

void	execute_builtin(t_mini *mini)
{
	(void)mini;
}
