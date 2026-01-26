/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 16:44:31 by ranhaia-          #+#    #+#             */
/*   Updated: 2026/01/17 06:18:28 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd	*create_node(char **cmd_args)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->cmd_args = cmd_args;
	new->cmd_path = NULL;
	new->fd_in = STDIN_FILENO;
	new->fd_out = STDOUT_FILENO;
	new->process_pid = -1;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}


void	print_cmd_list(t_cmd *cmd_list)
{
	t_cmd	*temp;
	int		i;

	if (!cmd_list)
		return ;
	temp = cmd_list;
	while (temp != NULL)
	{
		i = 0;
		printf("node t_cmd-> ");
		while (temp->cmd_args[i])
			printf("\"%s\" ", temp->cmd_args[i++]);
		printf("\n");
		temp = temp->next;
	}
}

void	insert_cmd_back(t_cmd **head, t_cmd *newnode)
{
	t_cmd	*temp;

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

void	free_cmds(t_cmd *cmd_list)
{
	t_cmd	*temp;
	int		i;

	if (!cmd_list)
		return ;
	while (cmd_list != NULL)
	{
		temp = cmd_list->next;
		if (cmd_list->cmd_args)
		{
			i = 0;
			while (cmd_list->cmd_args[i])
				free(cmd_list->cmd_args[i++]);
			free(cmd_list->cmd_args);
		}
		if (cmd_list->cmd_path)
			free(cmd_list->cmd_path);
		free(cmd_list);
		cmd_list = temp;
	}
	free(cmd_list);
}
