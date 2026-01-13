/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 15:20:34 by ranhaia-          #+#    #+#             */
/*   Updated: 2026/01/13 16:46:30 by ranhaia-         ###   ########.fr       */
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

void	handle_word(t_token **token_list, char *temp, int *i)
{
	char	*substr;
	int		start;

	start = *i;
	while ((temp[*i] != ' ' && !is_operator(&temp[*i])) && temp[*i])
		(*i)++;
	substr = ft_substr(temp, start, *i - start);
	insert_back(token_list, substr, TOKEN_WORD);
}

void	handle_quote(t_token **token_list, char *temp, int *i)
{
	char	*substr;
	char	quote;
	int		start;

	quote = '"';
	if (temp[*i] == '\'')
		quote = '\'';
	start = (*i)++;
	while (temp[*i] != quote && temp[*i])
		(*i)++;
	substr = ft_substr(temp, start, ++(*i) - start);
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
		if (temp[i] == '"' || temp[i] == '\'')
			handle_quote(&token_list, temp, &i);
		if (is_operator(&temp[i]))
			handle_operator(&token_list, temp, &i);
		if (temp[i] != ' ' && !is_operator(&temp[i]))
			handle_word(&token_list, temp, &i);
		if (!temp[i])
			break ;
		i++;
	}
	free(temp);
	return (token_list);
}
