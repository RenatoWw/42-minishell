/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 16:18:19 by ranhaia-          #+#    #+#             */
/*   Updated: 2026/01/26 20:50:31 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*search_env(t_mini *mini, char *str)
{
	t_env	*temp;
	char	*trimmed;
	char	*value;

	if (!mini->env_list)
		return (NULL);
	temp = mini->env_list;
	value = NULL;
	trimmed = ft_strtrim(str, "$\"");
	if (ft_strncmp(str, "$?", 4) == 0)
		return (ft_strdup(ft_itoa(mini->exit_code)));
	while (temp != NULL)
	{
		if (ft_strncmp(trimmed, temp->key, 30) == 0)
		{
			value = ft_strdup(temp->value);
			break ;
		}
		temp = temp->next;
	}
	free(trimmed);
	free(str);
	return (value);
}

void	replace_str(t_mini *mini, char **temp, int j)
{
	char	*newstr;

	newstr = search_env(mini, ft_substr(*temp, j, ft_strlen(*temp)));
	free(*temp);
	if (!newstr)
		*temp = ft_strdup("");
	else
		*temp = ft_strdup(newstr);
	free(newstr);
}

void	expand_variables(t_mini *mini)
{
	char	**temp;
	int		i;
	int		j;

	i = 0;
	temp = mini->cmd->cmd_args;
	while (temp[i])
	{
		j = 0;
		while (temp[i][j])
		{
			if (temp[i][j] == '\'')
				break ;
			if (temp[i][j] == '$')
			{
				replace_str(mini, &temp[i], j);
				break ;
			}
			j++;
		}
		i++;
	}
}
