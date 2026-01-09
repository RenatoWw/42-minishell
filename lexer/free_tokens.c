/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 17:06:10 by ranhaia-          #+#    #+#             */
/*   Updated: 2026/01/09 17:07:34 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_tokens(t_token *token_list)
{
	t_token	*temp;

	temp = token_list;
	while (!temp)
	{
		free(token_list->value);
		temp = temp->next;
	}
	free(token_list);
}
