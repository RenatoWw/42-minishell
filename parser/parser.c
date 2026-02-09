/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 14:37:55 by ranhaia-          #+#    #+#             */
/*   Updated: 2026/02/09 16:47:41 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	init_cmd(t_cmd *cmd)
{
	cmd->fd_in = STDIN_FILENO;
	cmd->fd_out = STDOUT_FILENO;
	cmd->cmd_path = NULL;
	cmd->process_pid = -1;
	cmd->next = NULL;
	cmd->prev = NULL;
}

static int	is_redirection(t_token *token)
{
	if (token->type == TOKEN_REDIRECT_IN)
		return (1);
	if (token->type == TOKEN_REDIRECT_OUT)
		return (1);
	if (token->type == TOKEN_APPEND)
		return (1);
	if (token->type == TOKEN_HEREDOC)
		return (1);
	return (0);
}

int	fill_cmd_data(t_cmd *new_cmd, t_token **temp, t_mini *mini)
{
	int	i;

	i = 0;
	while (*temp && (*temp)->type != TOKEN_PIPE)
	{
		if (is_redirection(*temp))
		{
			if (!(*temp)->next)
				return (1);
			if (handle_redirections(*temp, &new_cmd, mini))
				return (1);
			*temp = (*temp)->next->next;
			continue ;
		}
		if ((*temp)->type == TOKEN_WORD)
		{
			new_cmd->cmd_args[i] = ft_strdup((*temp)->value);
			if (!new_cmd->cmd_args[i])
				return (1);
			i++;
		}
		*temp = (*temp)->next;
	}
	return (0);
}

t_cmd	*parse_tokens(t_token *token_list, t_mini *mini)
{
	t_cmd	*cmd_list;
	t_cmd	*new_cmd;
	t_token	*temp;

	if (!token_list || verify_syntax(token_list, &mini->exit_code))
		return (NULL);
	cmd_list = NULL;
	temp = token_list;
	while (temp)
	{
		new_cmd = ft_calloc(1, sizeof(t_cmd));
		if (!new_cmd)
			return (free_cmds(cmd_list));
		init_cmd(new_cmd);
		new_cmd->cmd_args = ft_calloc(count_words(temp) + 1,
				sizeof(char *));
		if (!new_cmd->cmd_args)
			return (free_cmds(cmd_list));
		if (fill_cmd_data(new_cmd, &temp, mini))
			return (free_cmds(cmd_list));
		insert_cmd_back(&cmd_list, new_cmd);
		if (temp)
			temp = temp->next;
	}
	return (cmd_list);
}
