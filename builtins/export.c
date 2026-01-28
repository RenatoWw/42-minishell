/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 19:55:24 by ranhaia-          #+#    #+#             */
/*   Updated: 2026/01/27 18:53:42 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sort_and_print(t_env **env_add, int len)
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
	sort_and_print(env_add, list_size((t_token *)env));
	i = 0;
	free(env_add);
}

int	export_builtin(t_mini *mini, char **args)
{
	int		j;

	if (!args[1])
	{
		print_env(mini->env_list);
		return (0);
	}
	if (ft_strchr(args[1], '=') == NULL)
	{
		insert_key_back(&mini->env_list,
			ft_substr(args[1], 0, ft_strlen(args[1])), ft_strdup("")
			);
		return (0);
	}
	j = 0;
	while (args[1][j])
	{
		if (args[1][j] == '=')
			insert_key_back(&mini->env_list, ft_substr(args[1], 0, j),
				ft_substr(args[1], j + 1, ft_strlen(args[1]))
				);
		j++;
	}
	return (0);
}
