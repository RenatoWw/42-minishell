/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teste_execute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 12:53:07 by ranhaia-          #+#    #+#             */
/*   Updated: 2026/01/20 12:57:21 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**make_args(char *a, char *b, char *c)
{
	char	**args;

	args = malloc(sizeof(char *) * 4);
	if (!args)
		return (NULL);
	args[0] = a;
	args[1] = b;
	args[2] = c;
	args[3] = NULL;
	return (args);
}

void	test_pipe(char **envp)
{
	t_cmd	*cmd1;
	t_cmd	*cmd2;

	cmd1 = cmd_new();
	cmd2 = cmd_new();
	cmd1->cmd_args = make_args("ls", NULL, NULL);
	cmd2->cmd_args = make_args("wc", "-l", NULL);
	cmd1->next = cmd2;
	cmd2->prev = cmd1;
	printf("=== TESTE PIPE ===\n");
	execute_cmds(cmd1, envp);
}

void	test_redirect(char **envp)
{
	t_cmd	*cmd;

	cmd = cmd_new();
	cmd->cmd_args = make_args("echo", "hi", NULL);
	cmd->fd_out = open("a.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (cmd->fd_out < 0)
		perror("open");
	printf("=== TESTE REDIRECT ===\n");
	execute_cmds(cmd, envp);
}

void	test_input(char **envp)
{
	t_cmd	*cmd;

	cmd = cmd_new();
	cmd->cmd_args = make_args("cat", NULL, NULL);
	cmd->fd_in = open("a.txt", O_RDONLY);
	if (cmd->fd_in < 0)
		perror("open");
	printf("=== TESTE INPUT ===\n");
	execute_cmds(cmd, envp);
}
