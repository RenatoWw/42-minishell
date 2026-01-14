/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 18:22:27 by ranhaia-          #+#    #+#             */
/*   Updated: 2026/01/13 21:20:48 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "includes/libft/libft.h"

# define RED "\033[31m"
# define GREEN "\033[32m"
# define RESET "\033[0m"

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
}	t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_cmd
{
	char			**cmd_args;
	char			*cmd_path;
	int				fd_in;
	int				fd_out;
	pid_t			process_pid;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}	t_cmd;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
	struct s_env	*prev;
}	t_env;

typedef struct s_mini
{
	t_env	*env_list;
	t_token	*tokens;
	t_cmd	*cmd;
	char	*input;
	int		exit_code;
	int		original_stdin;
	int		original_stdout;
}	t_mini;

t_token		*create_token(char *value, t_token_type type);
int			list_size(t_token *head);
void		insert_front(t_token **head, char *value, t_token_type type);
void		insert_back(t_token **head, char *value, t_token_type type);
t_token		*assign_tokens(t_mini *mini);
void		print_tokens(t_token *head);
void		free_tokens(t_token *token_list);

t_cmd		*parse_tokens(t_token *token_list);
int			print_error(char *token_value);
int			invalid_pipe(t_token *temp);

#endif