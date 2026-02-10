/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 19:55:24 by ranhaia-          #+#    #+#             */
/*   Updated: 2026/02/09 20:16:25 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	sort_and_print(t_env **env_add, int len)
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

static void	print_env(t_env *env)
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

static void	handle_export_arg(t_mini *mini, char *arg)
{
	char	*key;
	char	*value;
	char	*equal_sign;
	t_env	*existing_node;

	equal_sign = ft_strchr(arg, '=');
	if (equal_sign)
	{
		key = ft_substr(arg, 0, equal_sign - arg);
		value = ft_strdup(equal_sign + 1);
	}
	else
	{
		key = ft_strdup(arg);
		value = NULL;
	}
	if (!is_valid_env_key(key))
	{
		printf(RED "export: `%s': not a valid identifier\n" RESET, arg);
		free(key);
		if (value)
			free(value);
		return ;
	}
	existing_node = find_env_node(mini->env_list, key);
	if (existing_node)
	{
		if (value)
		{
			free(existing_node->value);
			existing_node->value = value;
		}
		free(key);
	}
	else
	{
		if (!value)
			value = ft_strdup("");
		insert_key_back(&mini->env_list, key, value);
	}
}

int	export_builtin(t_mini *mini, char **args)
{
	int		i;

	i = 1;
	if (!args[1])
	{
		print_env(mini->env_list);
		return (0);
	}
	while (args[i])
	{
		handle_export_arg(mini, args[i]);
		i++;
	}
	return (0);
}
