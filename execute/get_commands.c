/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 13:04:03 by dapinhei          #+#    #+#             */
/*   Updated: 2026/01/17 02:50:51 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*cmd_new(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->cmd_args = NULL;
	cmd->cmd_path = NULL;
	cmd->fd_in = STDIN_FILENO;
	cmd->fd_out = STDOUT_FILENO;
	cmd->process_pid = -1;
	cmd->next = NULL;
	cmd->prev = NULL;
	return (cmd);
}

void	cmd_add_back(t_cmd **list, t_cmd *new)
{
	t_cmd	*tmp;

	if (!*list)
	{
		*list = new;
		return;
	}
	tmp = *list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
}

void	add_arg(t_cmd *cmd, char *value)
{
	int		i;
	int		j;
	char	**new;

	i = 0;
	while (cmd->cmd_args && cmd->cmd_args[i])
		i++;

	new = malloc(sizeof(char *) * (i + 2));
	if (!new)
		return ;

	j = 0;
	while (j < i)
	{
		new[j] = cmd->cmd_args[j];
		j++;
	}
	new[i] = ft_strdup(value);
	new[i + 1] = NULL;

	free(cmd->cmd_args);
	cmd->cmd_args = new;
}

void	handle_redirect_out(t_cmd *cmd, char *file)
{
	if (cmd->fd_out != STDOUT_FILENO)
		close(cmd->fd_out);

	cmd->fd_out = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (cmd->fd_out < 0)
		perror(file);
}

char	*find_cmd_path(char *cmd, char **envp)
{
	char	**paths;
	char	*full;
	int		i;

	i = 0;
	if (!cmd)
		return (NULL);
	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
		i++;
	if (!envp[i])
		return (NULL);
	paths = ft_split(envp[i] + 5, ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		full = ft_strjoin(paths[i], "/");
		full = ft_strjoin_free(full, cmd);
		if (access(full, X_OK) == 0)
		{
			free_split(paths);
			return (full);
		}
		free(full);
		i++;
	}
	free_split(paths);
	return (NULL);
}


