/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 05:12:23 by ranhaia-          #+#    #+#             */
/*   Updated: 2026/01/31 05:15:58 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_mini	*get_data(t_mini *new_ptr)
{
	static t_mini	*ptr_backup;

	if (new_ptr)
		ptr_backup = new_ptr;
	return (ptr_backup);
}
