/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 19:55:24 by ranhaia-          #+#    #+#             */
/*   Updated: 2026/01/26 21:02:40 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_env(t_env *env)
{
	t_env	*temp;

	temp = env;
	if (!temp)
		return ;
	while (temp != NULL)
	{
		printf("declare -x %s=\"%s\"\n", temp->key, temp->value);
		temp = temp->next;
	}
}

void	export_builtin(t_mini *mini)
{
	char	**cmd_args;
	int		j;

	cmd_args = mini->cmd->cmd_args;
	if (!cmd_args[1])
		return (print_env(mini->env_list));
	if (ft_strchr(cmd_args[1], '=') == NULL)
	{
		insert_key_back(&mini->env_list,
			ft_substr(cmd_args[1], 0, ft_strlen(cmd_args[1])),
			ft_strdup("")
			);
		return ;
	}
	j = 0;
	while (cmd_args[1][j])
	{
		if (cmd_args[1][j] == '=')
			insert_key_back(&mini->env_list,
				ft_substr(cmd_args[1], 0, j),
				ft_substr(cmd_args[1], j + 1, ft_strlen(cmd_args[1]))
				);
		j++;
	}
}
