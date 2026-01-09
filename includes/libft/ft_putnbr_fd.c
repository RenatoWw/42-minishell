/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 18:27:12 by ranhaia-          #+#    #+#             */
/*   Updated: 2025/07/22 19:04:13 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long int	nb;
	char		str[12];
	int			i;

	nb = n;
	if (nb == 0)
		write(fd, "0", 1);
	if (nb < 0)
	{
		write(fd, "-", 1);
		nb = -nb;
	}
	i = 0;
	while (nb > 0)
	{
		str[i++] = nb % 10 + '0';
		nb /= 10;
	}
	while (i > 0)
		write(fd, &str[--i], 1);
}

// #include <fcntl.h>

// int	main(void)
// {
// 	int	fd;

// 	fd = open("renato", O_RDWR | O_CREAT, 0777);
// 	ft_putnbr_fd(-42, fd);
// 	return (0);
// }
