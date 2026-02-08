/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapinhei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 07:09:34 by dapinhei          #+#    #+#             */
/*   Updated: 2026/02/08 07:09:36 by dapinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_quoted(char *delimiter)
{
	if (!delimiter)
		return (0);
	if (delimiter[0] == '\'' || delimiter[0] == '"')
		return (1);
	return (0);
}

static char	*remove_quotes(char *delimiter)
{
	int	len;

	len = ft_strlen(delimiter);
	if ((delimiter[0] == '\'' && delimiter[len - 1] == '\'')
		|| (delimiter[0] == '"' && delimiter[len - 1] == '"'))
		return (ft_substr(delimiter, 1, len - 2));
	return (ft_strdup(delimiter));
}

static void	write_line(int fd, char *line)
{
	write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
}

static void	heredoc_loop(int fd, char *delimiter, int expand, t_mini *mini)
{
	char	*line;
	char	*expanded;

	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (!ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1))
		{
			free(line);
			break ;
		}
		if (expand)
		{
			expanded = expand_string(line, mini);
			write_line(fd, expanded);
			free(expanded);
		}
		else
			write_line(fd, line);
		free(line);
	}
}

int	handle_heredoc(char *delimiter, t_cmd *cmd, t_mini *mini)
{
	int		fd[2];
	int		expand;
	char	*clean_delimiter;

	if (pipe(fd) == -1)
		return (perror("pipe"), 1);
	expand = !is_quoted(delimiter);
	clean_delimiter = remove_quotes(delimiter);
	heredoc_loop(fd[1], clean_delimiter, expand, mini);
	close(fd[1]);
	cmd->fd_in = fd[0];
	free(clean_delimiter);
	return (0);
}
