/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 17:03:38 by ranhaia-          #+#    #+#             */
/*   Updated: 2025/07/18 17:34:15 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned char	*current;
	int				i;

	i = 0;
	current = 0;
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
			current = (unsigned char *) &s[i];
		i++;
	}
	if (s[i] == '\0' && c == '\0')
		current = (unsigned char *) &s[i];
	if (current)
		return ((char *)current);
	return (NULL);
}

// int	main(void)
// {
// 	char	*str;

// 	str = "tenato reneiro renate";
// 	printf("%c\n\n", 't' + 256);
// 	printf("%p\n%s", &str[0], ft_strrchr(str, 't' + 256));
// 	return (0);
// }
