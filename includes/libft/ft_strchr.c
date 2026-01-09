/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 13:52:51 by ranhaia-          #+#    #+#             */
/*   Updated: 2025/07/15 21:18:56 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char			*ptr;
	unsigned char	ch;

	ptr = (char *) s;
	ch = (unsigned char) c;
	while (*s)
	{
		if (*s == ch)
		{
			ptr = (char *) s;
			return (ptr);
		}
		else
			s++;
	}
	if (*s == '\0' && ch == '\0')
	{
		ptr = (char *) s;
		return (ptr);
	}
	return (NULL);
}

// int	main(void)
// {
// 	char	*str;

// 	str = "tripaegtsr";
// 	printf("%s : ", ft_strchr(str, 't' + 256));
// 	printf("%c", 't' + 256);
// 	return (0);
// }
