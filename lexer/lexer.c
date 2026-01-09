/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 19:17:53 by ranhaia-          #+#    #+#             */
/*   Updated: 2026/01/09 14:38:14 by ranhaia-         ###   ########.fr       */
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
