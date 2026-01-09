/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 15:58:05 by ranhaia-          #+#    #+#             */
/*   Updated: 2025/07/13 16:07:57 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*str;
	size_t			i;

	i = 0;
	str = (unsigned char *) s;
	while (i < n)
	{
		str[i] = '\0';
		i++;
	}
}

// int	main(void)
// {
// 	char	str[10] = "testeteste";
// 	int		i;

// 	i = 0;
// 	// str = "testeteste";
// 	while (i < 10)
// 	{
// 		printf("%d\n", str[i]);
// 		i++;
// 	}
// 	ft_bzero(str, 10);
// 	i = 0;
// 	printf("\n\n");
// 	while (i < 10)
// 	{
// 		printf("%d", str[i]);
// 		i++;
// 	}
// 	return (0);
// }
