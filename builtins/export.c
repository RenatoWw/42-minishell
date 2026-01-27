/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 19:55:24 by ranhaia-          #+#    #+#             */
/*   Updated: 2026/01/27 18:10:25 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sort_address(t_env **env_add, int len)
{
	t_env	*temp;
	int		i;
	int		j;

	i = 0;
	while (i < len - 1)
	{
		j = -1;
		while (++j < len - i - 1)
		{
			if (ft_strncmp(env_add[j]->key, env_add[j + 1]->key, 30) > 0)
			{
				temp = env_add[j];
				env_add[j] = env_add[j + 1];
				env_add[j + 1] = temp;
			}
		}
		i++;
	}
	i = 0;
	while (i < len)
	{
		printf("declare -x %s=\"%s\"\n", env_add[i]->key, env_add[i]->value);
		i++;
	}
}

void	print_env(t_env *env)
{
	t_env	**env_add;
	t_env	*temp;
	int		i;

	temp = env;
	if (!temp)
		return ;
	env_add = ft_calloc(list_size((t_token *)env), sizeof(t_env *));
	i = 0;
	while (temp != NULL)
	{
		env_add[i] = temp;
		temp = temp->next;
		i++;
	}
	sort_address(env_add, list_size((t_token *)env));
	i = 0;
	free(env_add);
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
