/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 20:49:22 by ranhaia-          #+#    #+#             */
/*   Updated: 2025/07/23 13:58:33 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (lst == 0 || new == 0)
		return ;
	new->next = *lst;
	*lst = new;
}

// static void	print_list(t_list *list)
// {
// 	while (list != NULL)
// 	{
// 		printf("%s\n", (char *)list->content);
// 		list = list->next;
// 	}
// }

// int	main(void)
// {
// 	t_list	*new;

// 	new = ft_lstnew("42");
// 	new->next = ft_lstnew("renato");
// 	new->next->next = ft_lstnew("quarenta e dois");
// 	while (new != NULL)
// 		new = new->next;
// 	new = ft_lstnew("teste");
// 	ft_lstadd_back(&new, ft_lstnew("banana"));
// 	ft_lstadd_back(&new, ft_lstnew("açaí"));
// 	// ft_lstlast(new);
// 	print_list(new);
// 	printf("size: %d\n", ft_lstsize(new));
// }
