/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 13:54:50 by ranhaia-          #+#    #+#             */
/*   Updated: 2025/07/24 13:55:43 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	signal;
	int	num;

	signal = 1;
	num = 0;
	while (*nptr == ' ' || (*nptr >= 9 && *nptr <= 13))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			signal *= -1;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		num = (num * 10) + *nptr++ - '0';
	}
	return (num * signal);
}

// int	main(void)
// {
// 	// char	*num;

// 	// num = "-1";
// 	// printf("%d\n", ft_atoi(num));

// 	printf("ft:   %d\n", ft_atoi("+\t\v\f\r\n \f1234"));
// 	printf("atoi: %d\n", atoi("+\t\v\f\r\n \f1234"));
// 	printf("ft:   %d\n", ft_atoi("\t\n\v\f\r + 42"));
// 	printf("atoi: %d\n", atoi("\t\n\v\f\r + 42"));
// 	return (0);
// }
