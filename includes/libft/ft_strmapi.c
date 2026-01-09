/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 17:56:50 by ranhaia-          #+#    #+#             */
/*   Updated: 2025/07/22 21:25:35 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// static char	funcao(unsigned int n, char c)
// {
// 	return (n + c);
// }

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int		i;
	char				*newstr;

	newstr = ft_calloc(ft_strlen(s) + 1, sizeof(char));
	if (newstr == NULL)
		return (NULL);
	i = 0;
	while (s[i])
	{
		newstr[i] = f(i, s[i]);
		i++;
	}
	return (newstr);
}

// int	main(void)
// {
// 	char	*str;

// 	str = "renato";
// 	printf("%s", ft_strmapi(str, funcao));
// 	return (0);
// }
