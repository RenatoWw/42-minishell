/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 18:43:30 by ranhaia-          #+#    #+#             */
/*   Updated: 2025/07/23 18:01:42 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		len;
	char	*newstring;

	len = ft_strlen((char *)s);
	newstring = malloc(sizeof(char) * (len + 1));
	if (newstring == NULL)
		return (NULL);
	len = 0;
	while (s[len])
	{
		newstring[len] = s[len];
		len++;
	}
	newstring[len] = '\0';
	return (newstring);
}

// int	main(void)
// {
// 	char	*s1;

// 	s1 = "osasco";
// 	ft_strdup(s1);
// 	return (0);
// }
