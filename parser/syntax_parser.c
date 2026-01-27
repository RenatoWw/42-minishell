/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 14:52:59 by ranhaia-          #+#    #+#             */
/*   Updated: 2026/01/26 19:39:12 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	print_error(char *token_value)
{
	ft_putstr_fd(RED, 2);
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
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
	if (temp->type == TOKEN_APPEND && temp->next == NULL)
		return (print_error(NULL));
	else if (temp->type == TOKEN_REDIRECT_IN && temp->next == NULL)
		return (print_error(NULL));
	else if (temp->type == TOKEN_REDIRECT_OUT && temp->next == NULL)
		return (print_error(NULL));
	else if (temp->type == TOKEN_APPEND
		&& temp->next->type == TOKEN_REDIRECT_OUT)
		return (print_error(">"));
	else if (temp->type == TOKEN_REDIRECT_OUT
		&& temp->next->type == TOKEN_APPEND)
		return (print_error(">>"));
	else if (temp->type == TOKEN_HEREDOC && temp->prev == NULL)
		return (print_error(NULL));
	else if (temp->type == TOKEN_HEREDOC && temp->next == NULL)
		return (print_error(NULL));
	return (0);
}

int	unclosed_quote(char *value)
{
	int		single_quote;
	int		double_quote;
	int		i;

	i = 0;
	single_quote = 0;
	double_quote = 0;
	while (value[i])
	{
		if (value[i] == '\'')
			single_quote++;
		if (value[i] == '"')
			double_quote++;
		i++;
	}
	if (single_quote == 1 || double_quote == 1)
		return (print_error("quote"));
	return (0);
}

int	verify_syntax(t_token *token_list, int *exit_code)
{
	t_token	*temp;

	temp = token_list;
	while (temp != NULL)
	{
		if (unclosed_quote(temp->value) == 1)
		{
			*exit_code = 2;
			return (1);
		}
		if (invalid_pipe(temp) == 1 || invalid_red(temp) == 1)
		{
			*exit_code = 2;
			return (1);
		}
		temp = temp->next;
	}
	*exit_code = 0;
	return (0);
}
