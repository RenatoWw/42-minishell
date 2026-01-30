/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 20:17:07 by ranhaia-          #+#    #+#             */
/*   Updated: 2026/01/29 20:52:22 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	cd_builtin(t_mini *mini, char **args)
{
	t_env	*home;

	home = search_node(mini->env_list, "HOME");
	if (!args[1])
	{
		if (!home)
		{
			ft_putstr_fd(RED "cd: HOME not set\n" RESET, 2);
			return (1);
		}
		if (chdir(home->value) == -1)
		{
			perror("cd");
			return (1);
		}
		return (0);
	}
	if (chdir(args[1]) == -1)
	{
		perror("cd");
		return (1);
	}
	return (0);
}
