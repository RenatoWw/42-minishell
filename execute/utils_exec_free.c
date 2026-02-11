/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 04:17:56 by ranhaia-          #+#    #+#             */
/*   Updated: 2026/02/11 04:18:25 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	clean_invalid_cmd(t_mini *mini, char **envp)
{
	free_split(envp);
	free_all(mini);
	free_envp(mini->env_list);
	close(mini->original_stdin);
	close(mini->original_stdout);
	exit(0);
}

void	clean_child(char **envp, t_mini *mini)
{
	free_split(envp);
	free_all(mini);
	free_envp(mini->env_list);
	close(mini->original_stdin);
	close(mini->original_stdout);
}
