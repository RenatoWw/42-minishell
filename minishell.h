/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 18:22:27 by ranhaia-          #+#    #+#             */
/*   Updated: 2026/01/26 18:08:58 by ranhaia-         ###   ########.fr       */
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
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/wait.h>
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

/* Lexer functions */
t_token		*create_token(char *value, t_token_type type);
int			list_size(t_token *head);
void		insert_back(t_token **head, char *value, t_token_type type);
t_token		*assign_tokens(t_mini *mini);
void		print_tokens(t_token *head);
void		free_tokens(t_token *token_list);
int			is_space(char chr);

/* Parser functions */
t_cmd		*parse_tokens(t_token *token_list, int *exit_code);
int			print_error(char *token_value);
int			invalid_pipe(t_token *temp);
int			verify_syntax(t_token *token_list, int *exit_code);
t_cmd		*create_node(char **cmd_args);
void		insert_cmd_back(t_cmd **head, t_cmd *newnode);
void		print_cmd_list(t_cmd *cmd_list);
void		*free_cmds(t_cmd *cmd_list);
int			fill_cmd_data(t_cmd *new_cmd, t_token **temp);
int			handle_redirections(t_token *temp, t_cmd **new_cmd);

/* Expander functions */
t_env		*create_envp_node(char *key, char *value);
void		copy_envp(t_mini *mini, char **envp);
void		insert_key_back(t_env **head, char *key, char *value);
void		free_envp(t_env *env_list);
void		expand_variables(t_mini *mini, char **envp);

/* Minishell utils */
void		restore_stdio(t_mini *mini);
void		free_all(t_mini *mini);
void		set_mini_args(t_mini *mini);
void		validate_argc(int argc, char **argv);

/*execute*/
t_cmd		*cmd_new(void);
void		cmd_add_back(t_cmd **list, t_cmd *new);
void		add_arg(t_cmd *cmd, char *value);
void		handle_redirect_out(t_cmd *cmd, char *file);
char		*find_cmd_path(char *cmd, char **envp);
void		child_process(t_cmd *cmd, int *pipefd, char **envp);
void		parent_process(t_cmd *cmd, int *pipefd);
void		wait_all(t_cmd *cmd, t_mini *mini);
void		execute_cmds(t_cmd *cmd_list, char **envp, t_mini *mini);
void		free_split(char **split);
char		*ft_strjoin_free(char *s1, char *s2);
int			handle_heredoc(t_cmd *cmd, char *delimiter);
char		*search_path(char *cmd, char **paths);

/*teste execute teste_execute.c */
char		**make_args(char *a, char *b, char *c);
void		test_pipe(char **envp);
void		test_redirect(char **envp);
void		test_input(char **envp);

#endif