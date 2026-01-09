/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 15:40:08 by ranhaia-          #+#    #+#             */
/*   Updated: 2025/07/22 20:38:03 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*newstring;
	size_t			newlen;
	unsigned int	strlen;

	strlen = ft_strlen(s);
	if (start > strlen)
		return (ft_calloc(1, 1));
	newlen = strlen - start;
	if (len > newlen)
		len = newlen;
	newstring = ft_calloc(len + 1, sizeof(char));
	if (newstring == NULL)
		return (NULL);
	ft_strlcpy(newstring, s + start, len + 1);
	return (newstring);
}

// int	main(void)
// {
// 	char	*str;
// 	char	*s;

// 	s = "0123456789";
// 	str = ft_substr("test", 1, 2);
// 	printf("%s", str);
// 	free(str);
// 	return (0);
// }
