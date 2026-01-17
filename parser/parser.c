/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 14:37:55 by ranhaia-          #+#    #+#             */
/*   Updated: 2026/01/17 02:17:45 by ranhaia-         ###   ########.fr       */
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

void	fill_cmd_data(t_cmd *new_cmd, t_token **temp)
{
	int	i;

	i = 0;
	while ((*temp) != NULL && (*temp)->type != TOKEN_PIPE)
	{
		if ((*temp)->type == TOKEN_REDIRECT_OUT
			|| (*temp)->type == TOKEN_APPEND)
		{
			*temp = (*temp)->next->next;
			continue ;
		}
		else if ((*temp)->type == TOKEN_REDIRECT_IN
			|| (*temp)->type == TOKEN_HEREDOC)
		{
			*temp = (*temp)->next->next;
			continue ;
		}
		else if ((*temp)->type == TOKEN_WORD)
			new_cmd->cmd_args[i++] = ft_strdup((*temp)->value);
		*temp = (*temp)->next;
	}
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
		fill_cmd_data(new_cmd, &temp);
		insert_cmd_back(&cmd_list, new_cmd);
		if (temp != NULL)
			temp = temp->next;
	}
	return (cmd_list);
}
