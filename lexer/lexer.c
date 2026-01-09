/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 15:20:34 by ranhaia-          #+#    #+#             */
/*   Updated: 2026/01/09 17:05:41 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*assign_tokens(t_mini *mini)
{
	t_token	*token_list;
	char	*temp;
	char	*substr;
	int		i;
	
	temp = ft_strtrim(mini->input, " \t\r");
	token_list = NULL;
	i = 0;
	while (temp[i])
	{
		// if (temp[i] == '|')
		// {
			// insert_back(&token_list, "|", TOKEN_PIPE);
			// i++;
			// break ;
		// }
		if (temp[i + 1] == ' ' || temp[i + 1] == '\0')
		{
			substr = ft_substr(temp, ft_strlen(temp) - i, i);
			insert_back(&token_list, substr, TOKEN_WORD);
			// printf("substr: %s\n", substr);
			// break ;
		}
		i++;
	}
	free(temp);
	return (token_list);
}
