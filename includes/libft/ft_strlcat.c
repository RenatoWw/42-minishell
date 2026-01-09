/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 19:14:12 by ranhaia-          #+#    #+#             */
/*   Updated: 2025/07/17 15:39:03 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	destlen;
	size_t	srclen;
	size_t	i;
	size_t	remainingspace;

	destlen = ft_strlen(dest);
	srclen = ft_strlen((char *)src);
	if (src == NULL)
		return (destlen);
	if (size == 0)
		return (srclen);
	if (destlen >= size)
		return (size + srclen);
	remainingspace = size - destlen - 1;
	i = 0;
	while (i < remainingspace && src[i])
	{
		dest[destlen + i] = src[i];
		i++;
	}
	dest[destlen + i] = '\0';
	return (destlen + srclen);
}

// int	main(void)
// {
// 	char		dest[30] = "BBBB";
// 	char		*src;
// 	size_t		size;

// 	src = "AAAAAAAAA";
// 	size = 3;
// 	printf("%d len\n", ft_strlen(src) + 3);
// 	printf("dest len: %zu\n", ft_strlcat(dest, src, 3));
// 	printf("dest: %s", dest);
// 	return (0);
// }
