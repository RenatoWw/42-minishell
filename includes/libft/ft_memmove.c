/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 16:19:40 by ranhaia-          #+#    #+#             */
/*   Updated: 2025/07/23 18:15:36 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	swap(unsigned char *dest, unsigned char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		dest[i] = src[i];
		i++;
	}
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*dest_cast;
	unsigned char	*src_cast;

	if (dest == NULL && src == NULL)
		return (NULL);
	dest_cast = (unsigned char *) dest;
	src_cast = (unsigned char *) src;
	if (dest_cast <= src_cast)
		swap(dest_cast, src_cast, n);
	else if (dest_cast > src_cast)
	{
		while (n > 0)
		{
			dest_cast[n - 1] = src_cast[n - 1];
			n--;
		}
	}
	return (dest_cast);
}

// int	main(void)
// {
// 	char	*arr;
// 	int		i;

// 	arr = malloc(sizeof(char) * 5);
// 	arr[0] = 'A';
// 	arr[1] = 'B';
// 	arr[2] = 'C';
// 	arr[3] = 'D';
// 	arr[4] = 'E';
// 	i = 0;
// 	printf("Array original:   ");
// 	while (i < 5)
// 	{
// 		printf("%c ", arr[i]);
// 		i++;
// 	}
// 	ft_memmove(&arr[1], &arr[0], 4);
// 	i = 0;
// 	printf("\nArray modificado: ");
// 	while (i < 5)
// 	{
// 		printf("%c ", arr[i]);
// 		i++;
// 	}
// 	free(arr);
// 	return (0);
// }
