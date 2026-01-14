/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 14:37:55 by ranhaia-          #+#    #+#             */
/*   Updated: 2026/01/14 18:21:21 by ranhaia-         ###   ########.fr       */
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

// int	handle_redirections(t_token *token_list, t_cmd *cmd)
// {
	
// }

t_cmd	*parse_tokens(t_token *token_list, int *exit_code)
{
	// t_cmd	*cmd;
	// char	**cmd_args;
	// t_token	*temp;
	// int		i;
	// int		j;
	// int		size;

	if (!token_list)
		return (NULL);
	if (verify_syntax(token_list, exit_code) == 1)
		return (NULL);
	// temp = token_list;
	// i = 0;
	
	// cmd_args = malloc(1);
	// cmd = create_node(cmd_args);
	// free(cmd_args);
	// free(cmd);
	return (NULL);
}
