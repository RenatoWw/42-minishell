/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_dir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 22:47:24 by ranhaia-          #+#    #+#             */
/*   Updated: 2026/01/30 22:47:41 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_home_path(t_mini *mini, char *pwd)
{
	t_env	*home;
	int		home_len;

	home = search_node(mini->env_list, "HOME");
	home_len = 0;
	if (home && ft_strncmp(pwd, home->value, ft_strlen(home->value)) == 0)
	{
		home_len = ft_strlen(home->value);
		return (ft_strjoin(PURPLE "~", pwd + home_len));
	}
	return (ft_strjoin(PURPLE, pwd));
}

char	*print_dir(t_mini *mini)
{
	char	pwd[2048];
	char	*home_path;
	char	*temp;
	char	*prompt;

	getcwd(pwd, 2048);
	home_path = get_home_path(mini, pwd);
	temp = ft_strjoin(PURPLE, home_path);
	prompt = ft_strjoin(temp, PURPLE "$ " RESET);
	free(home_path);
	free(temp);
	return (prompt);
}
