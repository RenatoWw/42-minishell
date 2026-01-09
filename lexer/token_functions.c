/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 19:17:53 by ranhaia-          #+#    #+#             */
/*   Updated: 2026/01/09 17:04:49 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*create_token(char *value, t_token_type type)
{
	t_token	*node;

	node = malloc(sizeof(t_token));
	if (!node)
		return (NULL);
	node->value = value;
	node->type = type;
	node->prev = NULL;
	node->next = NULL;
	return (node);
}

void	print_tokens(t_token *head)
{
	t_token	*temp;

	temp = head;
	if (!head)
		return ;
	while (temp->next != NULL)
	{
		printf("Value:%s\nType: %d\n", temp->value, temp->type);
		temp = temp->next;
	}
}

int	list_size(t_token *head)
{
	t_token	*temp;
	int		i;

	i = 0;
	temp = head;
	if (!temp)
		return (i);
	while (temp != NULL)
	{
		temp = temp->next;
		i++;
	}
	return (i);
}

void	insert_front(t_token **head, char *value, t_token_type type)
{
	t_token	*newnode;

	newnode = create_token(value, type);
	if (!(*head))
	{
		newnode->next = NULL;
		newnode->prev = NULL;
		*head = newnode;
		return ;
	}
	newnode->next = *head;
	newnode->prev = NULL;
	(*head)->prev = newnode;
	*head = newnode;
}

void	insert_back(t_token **head, char *value, t_token_type type)
{
	t_token	*newnode;
	t_token	*temp;

	newnode = create_token(value, type);
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
