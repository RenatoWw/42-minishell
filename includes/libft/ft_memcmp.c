/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 19:16:36 by ranhaia-          #+#    #+#             */
/*   Updated: 2025/07/18 14:17:37 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*first;
	unsigned char	*second;
	size_t			i;

	first = (unsigned char *) s1;
	second = (unsigned char *) s2;
	i = 0;
	while (i < n)
	{
		if (first[i] != second[i])
			return (first[i] - second[i]);
		i++;
	}
	return (0);
}

// int	main(void)
// {
// 	char	*s1 = "strogonoff de frango";
// 	char	*s2 = "strogonoff de carne";

// 	printf("%d", ft_memcmp(s1, s2, 15));
// 	return (0);
// }
