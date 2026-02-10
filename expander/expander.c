/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 16:18:19 by ranhaia-          #+#    #+#             */
/*   Updated: 2026/02/09 20:57:45 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*search_env(t_mini *mini, char *str)
{
	t_env	*temp;
	char	*trimmed;

	if (!mini->env_list)
		return (NULL);
	temp = mini->env_list;
	trimmed = ft_strtrim(str, "$\"");
	if (ft_strncmp(str, "$?", 4) == 0)
		return (ft_itoa(mini->exit_code));
	while (temp != NULL)
	{
		if (ft_strncmp(trimmed, temp->key, ft_strlen(temp->key)) == 0)
			return (ft_strdup(temp->value));
		temp = temp->next;
	}
	free(trimmed);
	return (NULL);
}

int	var_len(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '?')
		return (1);
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	return (i);
}

static char	*join_and_free(char *prefix, char *val, char *suffix, char *old)
{
	char	*temp;
	char	*new_str;

	temp = ft_strjoin(prefix, val);
	new_str = ft_strjoin(temp, suffix);
	free(prefix);
	free(val);
	free(suffix);
	free(temp);
	free(old);
	return (new_str);
}

void	replace_str(t_mini *mini, char **temp, int j)
{
	char	*key;
	char	*value;
	int		len_key;

	len_key = var_len(*temp + j + 1);
	key = ft_substr(*temp, j + 1, len_key);
	value = search_env(mini, key);
	if (!value)
		value = ft_strdup("");
	free(key);
	*temp = join_and_free(
			ft_substr(*temp, 0, j),
			value,
			ft_substr(*temp, j + 1 + len_key, ft_strlen(*temp)),
			*temp
			);
}

void	expand_variables(t_mini *mini)
{
	char	**temp;
	int		i;
	int		j;
	int		is_in_quote;

	i = 0;
	temp = mini->cmd->cmd_args;
	while (temp[i])
	{
		j = 0;
		is_in_quote = 0;
		while (temp[i][j])
		{
			if (temp[i][j] == '\'')
				is_in_quote = !is_in_quote;
			if (temp[i][j] == '$' && !is_in_quote)
			{
				replace_str(mini, &temp[i], j);
				j = -1;
				is_in_quote = 0;
			}
			j++;
		}
		remove_quote(&temp[i++]);
	}
}
