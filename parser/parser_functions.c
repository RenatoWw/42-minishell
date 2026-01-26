/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 16:44:31 by ranhaia-          #+#    #+#             */
/*   Updated: 2026/01/26 17:49:03 by ranhaia-         ###   ########.fr       */
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

int	handle_redirections(t_token *temp, t_cmd **new_cmd)
{
	if (temp->type == TOKEN_REDIRECT_OUT)
	{
		(*new_cmd)->fd_out = open(
				temp->next->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if ((*new_cmd)->fd_out == -1)
			return (1);
	}
	else if (temp->type == TOKEN_APPEND)
	{
		(*new_cmd)->fd_out = open(
				temp->next->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if ((*new_cmd)->fd_out == -1)
			return (1);
	}
	else if (temp->type == TOKEN_REDIRECT_IN)
	{
		(*new_cmd)->fd_in = open(temp->next->value, O_RDONLY);
		if ((*new_cmd)->fd_in == -1)
			return (1);
	}
	else if (temp->type == TOKEN_HEREDOC)
		if (handle_heredoc(*new_cmd, temp->next->value) != 0)
			return (1);
	return (0);
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

void	*free_cmds(t_cmd *cmd_list)
{
	t_cmd	*temp;
	int		i;

	if (!cmd_list)
		return (NULL);
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
	return (NULL);
}
