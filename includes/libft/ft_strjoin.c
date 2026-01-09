/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 16:06:03 by ranhaia-          #+#    #+#             */
/*   Updated: 2025/07/17 16:21:05 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*newstr;
	int		len;
	int		i;
	int		j;

	len = ft_strlen((char *)s1) + ft_strlen((char *)s2);
	newstr = malloc(sizeof(char) * len + 1);
	if (newstr == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		newstr[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		newstr[i++] = s2[j++];
	}
	newstr[i] = '\0';
	return (newstr);
}

// int	main(void)
// {
// 	return (0);
// }
