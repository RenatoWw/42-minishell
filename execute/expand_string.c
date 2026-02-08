/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapinhei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 07:12:29 by dapinhei          #+#    #+#             */
/*   Updated: 2026/02/08 07:12:33 by dapinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	var_len(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '?')
		return (1);
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	return (i);
}

static char	*get_var_value(char *name, t_mini *mini)
{
	t_env	*env;

	if (!ft_strncmp(name, "?", 2))
		return (ft_itoa(mini->exit_code));
	env = mini->env_list;
	while (env)
	{
		if (!ft_strncmp(env->key, name, ft_strlen(name) + 1))
			return (ft_strdup(env->value));
		env = env->next;
	}
	return (ft_strdup(""));
}

static char	*append_str(char *s1, char *s2)
{
	char	*res;

	if (!s1)
		return (ft_strdup(s2));
	res = ft_strjoin(s1, s2);
	free(s1);
	return (res);
}

char	*expand_string(char *input, t_mini *mini)
{
	int		i;
	int		len;
	char	*res;
	char	*name;
	char	*value;

	i = 0;
	res = ft_strdup("");
	while (input[i])
	{
		if (input[i] == '$' && input[i + 1])
		{
			len = var_len(&input[i + 1]);
			name = ft_substr(input, i + 1, len);
			value = get_var_value(name, mini);
			res = append_str(res, value);
			free(name);
			free(value);
			i += len + 1;
		}
		else
			res = append_str(res, (char [2]){input[i++], 0});
	}
	return (res);
}
