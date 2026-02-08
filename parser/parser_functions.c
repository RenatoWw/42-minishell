/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 16:44:31 by ranhaia-          #+#    #+#             */
/*   Updated: 2026/01/31 05:32:44 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 16:44:31 by ranhaia-          #+#    #+#             */
/*   Updated: 2026/02/08 00:00:00 by assistant         ###   ########.fr      */
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

static int	handle_output(t_token *temp, t_cmd **cmd)
{
	if (open_file(&(*cmd)->fd_out, temp->next->value,
			O_WRONLY | O_CREAT | O_TRUNC))
		return (1);
	return (0);
}

static int	handle_append(t_token *temp, t_cmd **cmd)
{
	if (open_file(&(*cmd)->fd_out, temp->next->value,
			O_WRONLY | O_CREAT | O_APPEND))
		return (1);
	return (0);
}

static int	handle_input(t_token *temp, t_cmd **cmd)
{
	if (open_file(&(*cmd)->fd_in, temp->next->value, O_RDONLY))
		return (1);
	return (0);
}

int	handle_redirections(t_token *temp, t_cmd **new_cmd, t_mini *mini)
{
	if (temp->type == TOKEN_REDIRECT_OUT)
		return (handle_output(temp, new_cmd));
	else if (temp->type == TOKEN_APPEND)
		return (handle_append(temp, new_cmd));
	else if (temp->type == TOKEN_REDIRECT_IN)
		return (handle_input(temp, new_cmd));
	else if (temp->type == TOKEN_HEREDOC)
	{
		if (handle_heredoc(temp->next->value, *new_cmd, mini))
			return (1);
	}
	return (0);
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

static void	free_cmd_args(char **args)
{
	int	i;

	i = 0;
	if (!args)
		return ;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
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
