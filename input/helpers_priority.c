/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_priority.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpalac <danpalac@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 09:41:59 by danpalac          #+#    #+#             */
/*   Updated: 2025/01/09 12:19:50 by danpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

int	get_priority(char *str)
{
	if (!str)
		return (-1);
	if (!ft_strncmp(str, "()", 2) || !ft_strncmp(str, "{}", 2))
		return (0);
	else if (!ft_strncmp(str, "&&", 2) || !ft_strncmp(str, "||", 2))
		return (1);
	else if (!ft_strncmp(str, ">", 1) || !ft_strncmp(str, "<", 1))
		return (2);
	else if (!ft_strncmp(str, "|", 1) || !ft_strncmp(str, "&", 1))
		return (3);
	else if (str && !ft_strchr(str, '=')) // word or quote
		return (4);
	else if (ft_strchr(str, '='))
		return (5);
	return (6);
}

// Función para obtener la prioridad de un operador
void	set_node_priority(t_mt *node, void *param)
{
	if (!node || !node->data)
		return ;
	(void)param;
	node->values.priority = get_priority(node->data);
}
