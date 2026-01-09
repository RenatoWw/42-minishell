/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 14:38:44 by ranhaia-          #+#    #+#             */
/*   Updated: 2025/07/24 14:20:22 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	digits(long int nb)
{
	int	digits;

	digits = 0;
	if (nb < 0)
		nb = -nb;
	if (nb < 10)
		return (1);
	while (nb > 0)
	{
		digits++;
		nb /= 10;
	}
	return (digits);
}

char	*ft_itoa(int n)
{
	char		*num;
	int			len;
	int			negative;
	long int	nb;

	nb = n;
	negative = 0;
	len = digits(nb);
	if (nb < 0)
	{
		negative = 1;
		nb = -nb;
		len++;
	}
	num = ft_calloc(len + 1, sizeof(char));
	if (num == NULL)
		return (NULL);
	while (len > 0)
	{
		num[--len] = (nb % 10) + '0';
		nb /= 10;
	}
	if (negative == 1)
		num[0] = '-';
	return (num);
}

// int	main(void)
// {
// 	printf("%s", ft_itoa(-2147483648));
// 	return (0);
// }
