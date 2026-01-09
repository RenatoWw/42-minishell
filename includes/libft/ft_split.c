/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 13:20:26 by ranhaia-          #+#    #+#             */
/*   Updated: 2025/07/25 13:35:36 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, char c)
{
	int	words;
	int	start;
	int	trigger;

	words = 0;
	trigger = 0;
	start = 0;
	while (s[start])
	{
		if (s[start] != c && trigger == 0)
		{
			trigger = 1;
			words++;
		}
		if (s[start] == c)
			trigger = 0;
		start++;
	}
	return (words);
}

static int	find_end(int index, char const *s, char c)
{
	int	end;

	while (s[index] != c && s[index] != '\0')
	{
		if (s[index + 1] == c || s[index + 1] == '\0')
			end = index;
		index++;
	}
	return (end);
}

static char	**free_mem(char **words)
{
	int	i;

	i = 0;
	while (words[i] != NULL)
		free(words[i++]);
	free(words);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**words;
	int		word_count;
	int		start;
	int		end;

	words = ft_calloc((count_words(s, c) + 1), sizeof(char *));
	if (!words)
		return (NULL);
	start = 0;
	word_count = 0;
	while (s[start] == c && s[start])
		start++;
	while (s[start])
	{
		end = find_end(start, s, c);
		words[word_count] = ft_substr(s, start, end - start + 1);
		if (!words[word_count++])
			return (free_mem(words));
		while (s[start] != c && s[start])
			start++;
		while (s[start] == c && s[start])
			start++;
	}
	return (words);
}

// int	main(void)
// {
// 	char	**words;
// 	char	*s1;
// 	int		start;

// 	start = 0;
// 	s1 = "      split       this for   me  !       ";
// 	words = ft_split(s1, ' ');
// 	while (words[start])
// 	{
// 		printf("%s", words[start]);
// 		start++;
// 	}
// 	printf("%s", words[start]);
// 	return (0);
// }