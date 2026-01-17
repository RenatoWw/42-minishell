/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 16:10:49 by ranhaia-          #+#    #+#             */
/*   Updated: 2026/01/17 06:37:45 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// depois pesquisar alternativas para as funções using_history e clear_history
// essas duas não estão no pdf, tem a rl_clear_history, mas vou ver isso depois

// t_env	*create_envp_node(char *key, char *value)
// {
// 	t_env	*node;

// 	node = malloc(sizeof(t_env));
// 	if (!node)
// 		return (NULL);
// 	node->key = key;
// 	node->value = value;
// 	node->prev = NULL;
// 	node->next = NULL;
// 	return (node);
// }

// void	insert_key_back(t_env **head, char *key, char *value)
// {
// 	t_env	*newnode;
// 	t_env	*temp;

// 	newnode = create_envp_node(key, value);
// 	if (!newnode)
// 		return ;
// 	if (!(*head))
// 	{
// 		*head = newnode;
// 		newnode->next = NULL;
// 		newnode->prev = NULL;
// 		return ;
// 	}
// 	temp = *head;
// 	while (temp->next != NULL)
// 		temp = temp->next;
// 	temp->next = newnode;
// 	newnode->next = NULL;
// 	newnode->prev = temp;
// }

// void	copy_envp(t_mini *mini, char **envp)
// {
// 	t_env	*env;
// 	int		i;

// 	i = 0;
// 	env = create_envp_node(NULL, NULL);
// 	mini->env_list = env;
// 	// printf("oi\n");
// 	while (envp[i] != NULL)
// 	{
// 		printf("%s\n", envp[i]);
// 		i++;
// 	}
// }

void	free_all(t_mini *mini)
{
	free_tokens(mini->tokens);
	free_cmds(mini->cmd);
	free(mini->input);
}

// multiplos fds
// ls > file1 > file 2 > file
// é preciso fechar o anterior, verificar se o stdin ou stdou mudou
// se sim, fechar ele e abrir novamente, para não ter fd leak

int	main(int argc, char **argv)
{
	t_mini	mini;

	if (argc != 1 && argv[1])
	{
		printf("Usage: ./minishell\n");
		return (1);
	}
	using_history();
	while (1)
	{
		mini.input = readline(GREEN "minishell> " RESET);
		if (!mini.input)
			break ;
		if (ft_strncmp(mini.input, "", 2))
			add_history(mini.input);
		printf("input: %s\n", mini.input);
		mini.tokens = assign_tokens(&mini);
		mini.cmd = parse_tokens(mini.tokens, &mini.exit_code);
		if (mini.cmd == NULL)
		{
			free_all(&mini);
			return (1);
		}
		print_cmd_list(mini.cmd);
		free_all(&mini);
	}
	clear_history();
	return (0);
}
