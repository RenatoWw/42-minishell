/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 13:15:11 by renato            #+#    #+#             */
/*   Updated: 2026/01/31 05:00:28 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (!ft_strncmp(cmd, "echo", 5))
		return (1);
	if (!ft_strncmp(cmd, "cd", 3))
		return (1);
	if (!ft_strncmp(cmd, "pwd", 4))
		return (1);
	if (!ft_strncmp(cmd, "export", 7))
		return (1);
	if (!ft_strncmp(cmd, "unset", 6))
		return (1);
	if (!ft_strncmp(cmd, "env", 4))
		return (1);
	if (!ft_strncmp(cmd, "exit", 5))
		return (1);
	return (0);
}

int	exec_builtin(char **args, t_mini *mini)
{
	if (!ft_strncmp(args[0], "echo", 5))
		return (echo_builtin(mini, args));
	if (!ft_strncmp(args[0], "cd", 3))
		return (cd_builtin(mini, args));
	if (!ft_strncmp(args[0], "pwd", 4))
		return (pwd_builtin(mini, args));
	if (!ft_strncmp(args[0], "export", 7))
		return (export_builtin(mini, args));
	if (!ft_strncmp(args[0], "unset", 6))
		return (unset_builtin(mini, args));
	if (!ft_strncmp(args[0], "env", 4))
		return (env_builtin(mini, args));
	if (!ft_strncmp(args[0], "exit", 5))
		return (exit_builtin(mini, args));
	return (1);
}
