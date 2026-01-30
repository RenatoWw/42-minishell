/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 17:52:31 by ranhaia-          #+#    #+#             */
/*   Updated: 2026/01/29 18:22:37 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static long long	ft_atoll(const char *nptr)
{
	int			signal;
	long long	num;

	signal = 1;
	num = 0;
	while (*nptr == ' ' || (*nptr >= 9 && *nptr <= 13))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			signal *= -1;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
		num = (num * 10) + *nptr++ - '0';
	return (num * signal);
}

static int	ft_isnumber(char *str)
{
	int		i;

	i = 0;
	if (!str || !str[0])
		return (0);
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	exit_builtin(t_mini *mini, char **args)
{
	long long	status;

	printf("exit\n");
	if (!args[1])
	{
		free_all(mini);
		free_envp(mini->env_list);
		exit(mini->exit_code);
	}
	if (ft_isnumber(args[1]) == 0)
	{
		ft_putstr_fd(RED "exit: numeric argument required\n" RESET, 2);
		free_all(mini);
		free_envp(mini->env_list);
		exit(2);
	}
	if (args[2])
	{
		ft_putstr_fd(RED "exit: too many arguments\n" RESET, 2);
		return (1);
	}
	status = ft_atoll(args[1]);
	free_all(mini);
	free_envp(mini->env_list);
	exit(status % 256);
}
