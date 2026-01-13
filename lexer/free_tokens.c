/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 17:06:10 by ranhaia-          #+#    #+#             */
/*   Updated: 2026/01/13 13:37:33 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_tokens(t_token *token_list)
{
	t_token	*temp;

	if (!token_list)
		return ;
	while (token_list != NULL)
	{
		temp = token_list->next;
		if (token_list->value)
			free(token_list->value);
		free(token_list);
		token_list = temp;
	}
	free(token_list);
}
