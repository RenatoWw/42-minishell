/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 15:20:34 by ranhaia-          #+#    #+#             */
/*   Updated: 2026/02/11 04:33:56 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_operator(char *temp)
{
	if ((*temp != '>' && *temp != '|') && *temp != '<')
		return (0);
	else
		return (1);
}

void	handle_operator(t_token **token_list, char *temp, int *i)
{
	if (temp[*i] == '>' && temp[*i + 1] == '>')
	{
		insert_back(token_list, ft_strdup(">>"), TOKEN_APPEND);
		(*i) += 2;
	}
	else if (temp[*i] == '<' && temp[*i + 1] == '<')
	{
		insert_back(token_list, ft_strdup("<<"), TOKEN_HEREDOC);
		(*i) += 2;
	}
	else
	{
		if (temp[*i] == '|')
			insert_back(token_list, ft_strdup("|"), TOKEN_PIPE);
		else if (temp[*i] == '>')
			insert_back(token_list, ft_strdup(">"), TOKEN_REDIRECT_OUT);
		else if (temp[*i] == '<')
			insert_back(token_list, ft_strdup("<"), TOKEN_REDIRECT_IN);
		(*i)++;
	}
}

void	handle_word(t_token **token_list, char *temp, int *i)
{
	char	*substr;
	int		start;
	char	quote;

	start = *i;
	quote = 0;
	while (temp[*i])
	{
		if (!quote && (temp[*i] == '\'' || temp[*i] == '"'))
			quote = temp[*i];
		else if (quote && temp[*i] == quote)
			quote = 0;
		if (!quote && (is_space(temp[*i]) || is_operator(&temp[*i])))
			break ;
		(*i)++;
	}
	substr = ft_substr(temp, start, *i - start);
	insert_back(token_list, substr, TOKEN_WORD);
}

t_token	*assign_tokens(t_mini *mini)
{
	t_token	*token_list;
	char	*temp;
	int		i;

	temp = ft_strtrim(mini->input, " \t\r");
	token_list = NULL;
	i = 0;
	while (temp[i])
	{
		while (is_space(temp[i]) == 1)
			i++;
		if (!temp[i])
			break ;
		if (is_operator(&temp[i]))
			handle_operator(&token_list, temp, &i);
		else
			handle_word(&token_list, temp, &i);
	}
	free(temp);
	return (token_list);
}
