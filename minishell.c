/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 16:10:49 by ranhaia-          #+#    #+#             */
/*   Updated: 2026/01/09 14:38:09 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// void	insert_front(t_token **head, int content)
// {
// 	t_token	*newnode;

// 	newnode = create_token(content);
// 	if (!(*head))
// 	{
// 		newnode->next = NULL;
// 		newnode->prev = NULL;
// 		*head = newnode;
// 		return ;
// 	}
// 	newnode->next = *head;
// 	newnode->prev = NULL;
// 	(*head)->prev = newnode;
// 	*head = newnode;
// }

// void	insert_back(t_token **head, int content)
// {
// 	t_token	*newnode;
// 	t_token	*temp;

// 	newnode = create_token(content);
// 	if (!(*head))
// 	{
// 		*head = newnode;
// 		newnode->next = NULL;
// 		newnode->prev = NULL;
// 		return ;
// 	}
// 	temp = *head;
// 	while (temp->next != NULL)
// 		temp = temp->next;
// 	temp->next = newnode;
// 	newnode->next = NULL;
// 	newnode->prev = temp;
// }

int	main(void)
{
	char	*line;

	using_history();
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (!ft_strncmp(line, "", 2))
			add_history(line);
		printf("%s\n", line);
		free(line);
	}
	clear_history();
	return (0);
}
