/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 14:43:07 by ranhaia-          #+#    #+#             */
/*   Updated: 2025/07/24 17:42:03 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t			max;
	size_t			i;
	unsigned char	*allocator;

	if (size == 0 || nmemb == 0)
		return (malloc(1));
	max = (size_t)-1 / size;
	if (nmemb > max)
		return (NULL);
	allocator = malloc(nmemb * size);
	if (allocator == NULL)
		return (NULL);
	i = 0;
	while (i < (nmemb * size))
		allocator[i++] = 0;
	return (allocator);
}

// int	main(void)
// {
// 	char	*str;

// 	printf("size_t max: %d\n\n", 2);
// 	str = ft_calloc(0, 0);
// 	printf("%d", str[0]);
// 	free(str);
// 	return (0);
// }
