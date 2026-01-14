/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 14:37:55 by ranhaia-          #+#    #+#             */
/*   Updated: 2026/01/13 21:21:05 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	print_error(char *token_value)
{
	ft_putstr_fd(RED, 2);
	ft_putstr_fd("minishell: syntax error near unexpected token '", 2);
	if (!token_value)
		ft_putstr_fd("newline", 2);
	else
		ft_putstr_fd(token_value, 2);
	ft_putstr_fd("'\n", 2);
	ft_putstr_fd(RESET, 2);
	return (1);
}

int	invalid_pipe(t_token *temp)
{
	if (temp->type == TOKEN_PIPE && temp->next == NULL)
		return (print_error(NULL));
	else if (temp->type == TOKEN_PIPE && temp->prev == NULL)
		return (print_error("|"));
	else if (temp->type == TOKEN_PIPE && temp->next->type == TOKEN_PIPE)
		return (print_error("|"));
	else if (temp->type == TOKEN_PIPE && temp->next->type == TOKEN_REDIRECT_IN)
		return (print_error("|"));
	else if (temp->type == TOKEN_PIPE && temp->next->type == TOKEN_REDIRECT_OUT)
		return (print_error("|"));
	else if (temp->type == TOKEN_PIPE && temp->next->type == TOKEN_APPEND)
		return (print_error("|"));
	else if (temp->type == TOKEN_PIPE && temp->prev->type == TOKEN_REDIRECT_IN)
		return (print_error("|"));
	else if (temp->type == TOKEN_PIPE && temp->prev->type == TOKEN_REDIRECT_OUT)
		return (print_error("|"));
	else if (temp->type == TOKEN_PIPE && temp->prev->type == TOKEN_APPEND)
		return (print_error("|"));
	return (0);
}

int	invalid_red(t_token *temp)
{
	if (temp->type == TOKEN_REDIRECT_IN && temp->next == NULL)
		return (print_error(NULL));
	else if (temp->type == TOKEN_REDIRECT_OUT && temp->next == NULL)
		return (print_error(NULL));
	else if (temp->type == TOKEN_APPEND
		&& temp->next->type == TOKEN_REDIRECT_OUT)
		return (print_error(">"));
	else if (temp->type == TOKEN_REDIRECT_OUT
		&& temp->next->type == TOKEN_APPEND)
		return (print_error(">>"));
	else if (temp->type == TOKEN_APPEND && temp->next == NULL)
		return (print_error(NULL));
	else if (temp->type == TOKEN_HEREDOC && temp->prev == NULL)
		return (print_error(NULL));
	else if (temp->type == TOKEN_HEREDOC && temp->next == NULL)
		return (print_error(NULL));
	return (0);
}

// setar exit_code corretamente, caso algum erro de sintaxe apareça

t_cmd	*parse_tokens(t_token *token_list)
{
	t_token	*temp;
	t_cmd	*cmd;

	cmd = NULL;
	if (!token_list)
		return (NULL);
	temp = token_list;
	while (temp != NULL)
	{
		if (invalid_pipe(temp) == 1)
			return (NULL);
		if (invalid_red(temp) == 1)
			return (NULL);
		temp = temp->next;
	}
	return (cmd);
}
