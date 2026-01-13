/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 15:20:34 by ranhaia-          #+#    #+#             */
/*   Updated: 2026/01/13 14:01:26 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_operator(t_token **token_list, char *temp, int *i)
{
	if (temp[*i] == '>' && temp[*i + 1] == '>')
	{
		insert_back(token_list, ft_strdup(">>"), TOKEN_APPEND);
		(*i)++;
	}
	else if (temp[*i] == '<' && temp[*i + 1] == '<')
	{
		insert_back(token_list, ft_strdup("<<"), TOKEN_HEREDOC);
		(*i)++;
	}
	else if (temp[*i] == '|')
		insert_back(token_list, ft_strdup("|"), TOKEN_PIPE);
	else if (temp[*i] == '>')
		insert_back(token_list, ft_strdup(">"), TOKEN_REDIRECT_OUT);
	else if (temp[*i] == '<')
		insert_back(token_list, ft_strdup("<"), TOKEN_REDIRECT_IN);
}

t_token	*assign_tokens(t_mini *mini)
{
	t_token	*token_list;
	char	*temp;
	// char	*substr;
	int		i;

	temp = ft_strtrim(mini->input, " \t\r");
	token_list = NULL;
	i = 0;
	while (temp[i])
	{
		handle_operator(&token_list, temp, &i);
		i++;
	}
	free(temp);
	return (token_list);
}
