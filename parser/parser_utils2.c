/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 16:48:57 by ranhaia-          #+#    #+#             */
/*   Updated: 2026/02/09 16:50:18 by ranhaia-         ###   ########.fr       */
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

	temp = cmd_list;
	while (temp)
	{
		i = 0;
		printf("node t_cmd-> ");
		while (temp->cmd_args && temp->cmd_args[i])
		{
			printf("\"%s\" ", temp->cmd_args[i]);
			i++;
		}
		printf("\n");
		temp = temp->next;
	}
}

void	insert_cmd_back(t_cmd **head, t_cmd *newnode)
{
	t_cmd	*temp;

	if (!head || !newnode)
		return ;
	if (!*head)
	{
		*head = newnode;
		return ;
	}
	temp = *head;
	while (temp->next)
		temp = temp->next;
	temp->next = newnode;
	newnode->prev = temp;
}

void	*free_cmds(t_cmd *cmd_list)
{
	t_cmd	*temp;

	while (cmd_list)
	{
		temp = cmd_list->next;
		if (cmd_list->fd_in > 2)
			close(cmd_list->fd_in);
		if (cmd_list->fd_out > 2)
			close(cmd_list->fd_out);
		free_cmd_args(cmd_list->cmd_args);
		if (cmd_list->cmd_path)
			free(cmd_list->cmd_path);
		free(cmd_list);
		cmd_list = temp;
	}
	return (NULL);
}
