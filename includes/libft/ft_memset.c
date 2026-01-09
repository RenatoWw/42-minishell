/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 14:23:52 by ranhaia-          #+#    #+#             */
/*   Updated: 2025/07/24 15:47:28 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*cast;
	size_t			i;

	cast = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		cast[i] = c;
		i++;
	}
	return (cast);
}

// int	main(void)
// {
// 	int	*arr;
// 	int	i;

// 	arr = malloc(sizeof(int) * 10);
// 	// a = 97
// 	ft_memset(arr, 97, 40);
// 	i = 0;
// 	while (i < 10)
// 	{
// 		printf("int: %d\nchar: %c\n", arr[i], arr[i]);
// 		i++;
// 	}
// 	free(arr);
// 	return (0);
// }
