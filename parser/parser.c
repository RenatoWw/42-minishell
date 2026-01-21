/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 14:37:55 by ranhaia-          #+#    #+#             */
/*   Updated: 2026/01/20 15:44:03 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_cmds(t_token *token_list)
{
	t_token	*temp;
	int		len;

	temp = token_list;
	len = 1;
	while (temp)
	{
		if (temp->type == 1)
			len++;
		temp = temp->next;
	}
	return (len);
}

int	count_words(t_token *token_list)
{
	t_token	*temp;
	int		len;

	temp = token_list;
	len = 0;
	while (temp != NULL && temp->type != TOKEN_PIPE)
	{
		if (temp->type == TOKEN_WORD)
			len++;
		if (temp->type >= TOKEN_REDIRECT_IN && temp->type <= TOKEN_HEREDOC)
			temp = temp->next;
		temp = temp->next;
	}
	return (len);
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
		(*new_cmd)->fd_in = open(temp->next->value, O_RDONLY, 0644);
		if ((*new_cmd)->fd_in == -1)
			return (1);
	}
	return (0);
}

int	fill_cmd_data(t_cmd *new_cmd, t_token **temp)
{
	int	i;

	i = 0;
	while ((*temp) != NULL && (*temp)->type != TOKEN_PIPE)
	{
		if ((*temp)->type == 3 || (*temp)->type == 4)
		{
			if (handle_redirections(*temp, &new_cmd) == 1)
				return (1);
			*temp = (*temp)->next->next;
			continue ;
		}
		else if ((*temp)->type == TOKEN_REDIRECT_IN
			|| (*temp)->type == TOKEN_HEREDOC)
		{
			if (handle_redirections(*temp, &new_cmd) == 1)
				return (1);
			*temp = (*temp)->next->next;
			continue ;
		}
		else if ((*temp)->type == TOKEN_WORD)
			new_cmd->cmd_args[i++] = ft_strdup((*temp)->value);
		*temp = (*temp)->next;
	}
	return (0);
}

t_cmd	*parse_tokens(t_token *token_list, int *exit_code)
{
	t_cmd	*cmd_list;
	t_cmd	*new_cmd;
	t_token	*temp;

	if (!token_list)
		return (NULL);
	if (verify_syntax(token_list, exit_code) == 1)
		return (NULL);
	temp = token_list;
	cmd_list = NULL;
	while (temp != NULL)
	{
		new_cmd = ft_calloc(1, sizeof(t_cmd));
		new_cmd->cmd_args = ft_calloc(count_words(temp) + 1, sizeof(char *));
		if (fill_cmd_data(new_cmd, &temp) == 1)
		{
			free_cmds(new_cmd);
			return (NULL);
		}
		insert_cmd_back(&cmd_list, new_cmd);
		if (temp != NULL)
			temp = temp->next;
	}
	return (cmd_list);
}
