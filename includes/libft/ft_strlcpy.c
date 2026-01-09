/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 17:39:43 by ranhaia-          #+#    #+#             */
/*   Updated: 2025/07/17 13:36:59 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;
	int		len;

	len = 0;
	if (size == 0)
	{
		while (src[len])
			len++;
		return (len);
	}
	i = 0;
	while (i < (size - 1) && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	while (src[i])
		i++;
	return (i);
}

// int	main(void)
// {
// 	char	dest[10];
// 	char	*src;

// 	src = "testee";
// 	printf("src len: %zu", ft_strlcpy(dest, src, 7));
// 	printf("\n%s", dest);
// 	return (0);
// }
