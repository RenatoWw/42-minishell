/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 05:25:59 by ranhaia-          #+#    #+#             */
/*   Updated: 2026/02/09 16:46:45 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	open_file(int *fd_ptr, char *path, int flags)
{
	if (*fd_ptr > 2)
		close(*fd_ptr);
	*fd_ptr = open(path, flags, 0644);
	if (*fd_ptr == -1)
	{
		perror(path);
		return (1);
	}
	return (0);
}

int	count_cmds(t_token *token_list)
{
	t_token	*temp;
	int		len;

	len = 1;
	temp = token_list;
	while (temp)
	{
		if (temp->type == TOKEN_PIPE)
			len++;
		temp = temp->next;
	}
	return (len);
}

int	count_words(t_token *token_list)
{
	t_token	*temp;
	int		len;

	len = 0;
	temp = token_list;
	while (temp && temp->type != TOKEN_PIPE)
	{
		if (temp->type == TOKEN_WORD)
			len++;
		if (temp->type >= TOKEN_REDIRECT_IN
			&& temp->type <= TOKEN_HEREDOC)
		{
			temp = temp->next;
			if (temp)
				temp = temp->next;
			continue ;
		}
		temp = temp->next;
	}
	return (len);
}
