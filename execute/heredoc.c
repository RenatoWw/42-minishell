/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 07:45:59 by dapinhei          #+#    #+#             */
/*   Updated: 2026/01/31 05:21:38 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	read_cmd(int pipefd[2], char *delimiter)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1) == 0)
		{
			free(line);
			break ;
		}
		write(pipefd[1], line, ft_strlen(line));
		write(pipefd[1], "\n", 1);
		free(line);
	}
}

static void	clean_up_heredoc(t_mini *mini_ptr, t_cmd *cmd, int pipefd[2])
{
	close(pipefd[1]);
	free_all(mini_ptr);
	free_envp(mini_ptr->env_list);
	free_cmds(cmd);
}

int	handle_heredoc(t_cmd *cmd, char *delimiter)
{
	int		pipefd[2];
	pid_t	pid;
	t_mini	*mini_ptr;

	mini_ptr = get_data(NULL);
	if (!cmd || !delimiter)
		return (1);
	if (pipe(pipefd) == -1)
		return (perror("pipe"), 1);
	pid = fork();
	if (pid < 0)
		return (perror("fork"), 1);
	if (pid == 0)
	{
		close(pipefd[0]);
		read_cmd(pipefd, delimiter);
		clean_up_heredoc(mini_ptr, cmd, pipefd);
		exit(0);
	}
	close(pipefd[1]);
	waitpid(pid, NULL, 0);
	if (cmd->fd_in != STDIN_FILENO)
		close(cmd->fd_in);
	cmd->fd_in = pipefd[0];
	return (0);
}
