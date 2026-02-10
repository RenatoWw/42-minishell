/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 20:07:15 by ranhaia-          #+#    #+#             */
/*   Updated: 2026/02/09 21:22:29 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_valid_env_key(char *key)
{
	int	i;

	i = 0;
	if (!ft_isalpha(key[0]) && key[0] != '_')
		return (0);
	i++;
	while (key[i] && key[i] != '=')
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	remove_quotes(char **temp)
{
	char	*str;
	char	*new_str;
	char	quote;
	int		len;

	str = *temp;
	len = ft_strlen(str);
	if (len < 2)
		return ;
	if (str[0] == '\'' || str[0] == '\"')
	{
		quote = str[0];
		if (str[len - 1] == quote)
		{
			new_str = ft_substr(str, 1, len - 2);
			free(*temp);
			*temp = new_str;
		}
	}
}

t_env	*find_env_node(t_env *env, char *key)
{
	t_env	*temp;

	temp = env;
	while (temp)
	{
		if (ft_strlen(temp->key) == ft_strlen(key)
			&& ft_strncmp(temp->key, key, ft_strlen(key)) == 0)
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}
