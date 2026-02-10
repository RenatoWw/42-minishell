/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 05:12:23 by ranhaia-          #+#    #+#             */
/*   Updated: 2026/02/09 21:06:10 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_mini	*get_data(t_mini *new_ptr)
{
	static t_mini	*ptr_backup;

	if (new_ptr)
		ptr_backup = new_ptr;
	return (ptr_backup);
}

char	**env_to_arr(t_env *env_list)
{
	int		size;
	int		i;
	char	**arr;
	char	*temp;

	size = list_size((t_token *) env_list);
	arr = malloc(sizeof(char *) * (size + 1));
	if (!arr)
		return (NULL);
	i = 0;
	while (i < size && env_list)
	{
		temp = ft_strjoin(env_list->key, "=");
		if (!temp)
			return (NULL);
		arr[i] = ft_strjoin(temp, env_list->value);
		free(temp);
		env_list = env_list->next;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

void	get_cmd_and_execute(t_mini *mini)
{
	char	**envp;

	mini->tokens = assign_tokens(mini);
	mini->cmd = parse_tokens(mini->tokens, mini);
	if (!mini->cmd)
	{
		free_all(mini);
		return ;
	}
	envp = env_to_arr(mini->env_list);
	expand_variables(mini);
	if (!mini->cmd->next && is_builtin(mini->cmd->cmd_args[0]))
		mini->exit_code = execute_single_builtin(mini);
	else
		execute_cmds(mini->cmd, envp, mini);
	free_split(envp);
	restore_stdio(mini);
	free_all(mini);
}

void	exit_properly(t_mini *mini)
{
	printf("exit\n");
	free_all(mini);
	free_envp(mini->env_list);
	close(mini->original_stdin);
	close(mini->original_stdout);
	exit(0);
}
