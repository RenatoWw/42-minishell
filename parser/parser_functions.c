/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 16:44:31 by ranhaia-          #+#    #+#             */
/*   Updated: 2026/02/09 16:50:42 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	free_cmd_args(char **args)
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
