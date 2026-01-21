/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 17:46:16 by ranhaia-          #+#    #+#             */
/*   Updated: 2026/01/21 18:12:01 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*create_envp_node(char *key, char *value)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = key;
	node->value = value;
	node->prev = NULL;
	node->next = NULL;
	return (node);
}

void	insert_key_back(t_env **head, char *key, char *value)
{
	t_env	*newnode;
	t_env	*temp;

	newnode = create_envp_node(key, value);
	if (!newnode)
		return ;
	if (!(*head))
	{
		*head = newnode;
		newnode->next = NULL;
		newnode->prev = NULL;
		return ;
	}
	temp = *head;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = newnode;
	newnode->next = NULL;
	newnode->prev = temp;
}

void	copy_envp(t_mini *mini, char **envp)
{
	int		i;
	int		j;
	char	*key;
	char	*value;
	int		value_int;

	i = 0;
	mini->env_list = NULL;
	while (envp[i] != NULL)
	{
		j = 0;
		while (envp[i][j] != '=')
			j++;
		key = ft_substr(envp[i], 0, j);
		value = ft_substr(envp[i], ++j, ft_strlen(envp[i]));
		if (ft_strncmp(key, "SHLVL", 6) == 1)
		{
			value_int = ft_atoi(value);
			free(value);
			value = ft_itoa(++value_int);
		}
		insert_key_back(&mini->env_list, key, value);
		i++;
	}
}

void	free_envp(t_env *env_list)
{
	t_env	*temp;

	if (!env_list)
		return ;
	while (env_list != NULL)
	{
		temp = env_list->next;
		if (env_list->key)
			free(env_list->key);
		if (env_list->value)
			free(env_list->value);
		free(env_list);
		env_list = temp;
	}
	free(env_list);
}
