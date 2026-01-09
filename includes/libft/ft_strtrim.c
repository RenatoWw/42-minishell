/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 16:25:49 by ranhaia-          #+#    #+#             */
/*   Updated: 2025/07/24 17:53:19 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ischarset(char c, char const *set)
{
	while (*set)
		if (c == *set++)
			return (1);
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*newstr;
	int		len;
	int		i;

	i = 0;
	if (s1 == NULL || set == NULL)
		return (NULL);
	while (*s1)
	{
		if (ischarset(*s1, set) == 1)
			s1++;
		else
			break ;
	}
	len = ft_strlen(s1);
	if (len == 0)
		return (ft_strdup(""));
	while (ischarset(s1[len - 1], set) == 1)
		len--;
	newstr = ft_calloc(len + 1, sizeof(char));
	if (newstr == NULL)
		return (NULL);
	return (ft_memcpy(newstr, s1, len));
}

// int	main(void)
// {
// 	printf("%s\n", ft_strtrim("#$#$renato#$#$", "#$"));
// 	return (0);
// }
