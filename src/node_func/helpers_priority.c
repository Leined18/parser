/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_priority.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpalac <danpalac@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 09:41:59 by danpalac          #+#    #+#             */
/*   Updated: 2025/02/24 12:55:36 by danpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

int	ft_get_priority(char *str)
{
	if (!str)
		return (-1);
	if (!ft_strncmp(str, "()", 2))
		return (6);
	if (!ft_strncmp(str, ">", 1) || !ft_strncmp(str, ">>", 2)
		|| !ft_strncmp(str, "<", 1) || !ft_strncmp(str, "<<", 2))
		return (5);
	if (!ft_strncmp(str, "|", 1))
		return (4);
	if (!ft_strncmp(str, "&&", 2) || !ft_strncmp(str, "||", 2))
		return (3);
	if (!ft_strchr(str, '='))
		return (2);
	if (ft_strchr(str, '='))
		return (1);
	return (0);
}

void	set_node_priority(t_mt *node, void *param)
{
	if (!node || !node->data)
		return ;
	(void)param;
	node->values.priority = ft_get_priority(node->data);
}
