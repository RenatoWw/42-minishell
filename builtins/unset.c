/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 19:04:07 by ranhaia-          #+#    #+#             */
/*   Updated: 2026/01/27 21:01:11 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	remove_envp_node(t_env **head, t_env *node)
{
	if (!head || !(*head) || !node)
		return ;
	if (*head == node)
		*head = node->next;
	if (node->next != NULL)
		node->next->prev = node->prev;
	if (node->prev != NULL)
		node->prev->next = node->next;
	free(node->key);
	free(node->value);
	free(node);
}

t_env	*search_node(t_env *head, char *key)
{
	t_env	*temp;

	temp = head;
	if (!temp)
		return (NULL);
	while (temp != NULL)
	{
		if (ft_strncmp(temp->key, key, 30) == 0)
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

int	unset_builtin(t_mini *mini, char **args)
{
	t_env	*node_to_del;
	int		i;

	if (!args[1])
	{
		printf(RED "unset: not enough arguments\n" RESET);
		return (0);
	}
	i = 1;
	while (args[i])
	{
		node_to_del = search_node(mini->env_list, args[i]);
		if (node_to_del != NULL)
			remove_envp_node(&mini->env_list, node_to_del);
		i++;
	}
	return (0);
}
