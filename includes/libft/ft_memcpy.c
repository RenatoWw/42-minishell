/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 16:08:48 by ranhaia-          #+#    #+#             */
/*   Updated: 2025/07/23 18:00:42 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*dest_cast;
	unsigned char	*src_cast;
	size_t			i;

	i = 0;
	if (dest == NULL && src == NULL)
		return (NULL);
	dest_cast = (unsigned char *) dest;
	src_cast = (unsigned char *) src;
	while (i < n)
	{
		dest_cast[i] = src_cast[i];
		i++;
	}
	return (dest_cast);
}

// int	main(void)
// {
// 	int	*arr;
// 	int	*src;
// 	int	i;

// 	printf("oi");
// 	arr = malloc(sizeof(int) * 10);
// 	src = malloc(sizeof(int) * 10);
// 	i = 0;
// 	printf("oi");
// 	while (i < 10)
// 	{
// 		src[i] = 5;
// 		i++;
// 	}
// 	printf("oi");
// 	ft_memcpy(arr, src, 40);
// 	i = 0;
// 	while (i < 10)
// 	{
// 		printf("int: %d\n", arr[i]);
// 		i++;
// 	}
// 	free(arr);
// 	free(src);
// 	return (0);
// }
