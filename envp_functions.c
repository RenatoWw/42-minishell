/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 17:46:16 by ranhaia-          #+#    #+#             */
/*   Updated: 2026/01/20 17:46:39 by ranhaia-         ###   ########.fr       */
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
	t_env	*env;
	int		i;

	i = 0;
	env = create_envp_node(NULL, NULL);
	mini->env_list = env;
	// printf("oi\n");
	while (envp[i] != NULL)
	{
		printf("%s\n", envp[i]);
		i++;
	}
}

