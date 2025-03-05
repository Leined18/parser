/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_priority.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-h <mvidal-h@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 09:41:59 by danpalac          #+#    #+#             */
/*   Updated: 2025/03/04 18:02:32 by mvidal-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

int	ft_get_priority(char *str)
{
	if (!str)
		return (-1);
	if (!ft_strncmp(str, "()", 2))
		return (7);
	if (!ft_strncmp(str, "&&", 2) || !ft_strncmp(str, "||", 2))
		return (6);
	if (!ft_strncmp(str, "<", 1) || !ft_strncmp(str, "<<", 2))
		return (5);
	if (!ft_strncmp(str, ">", 1) || !ft_strncmp(str, ">>", 2))
		return (4);
	if (!ft_strncmp(str, "|", 1))
		return (3);
	if (!ft_strchr(str, '='))
		return (2);
	if (ft_strchr(str, '='))
		return (1);
	return (0);
}

void	ft_set_priority(t_mt *list, void *param, void (*func)(t_mt *, void *))
{
	if (!list || !func)
		return ;
	ft_mtiter(list, param, func);
}

void	ft_set_node_priority(t_mt *node, void *param)
{
	if (!node || !node->data)
		return ;
	(void)param;
	node->values.priority = ft_get_priority(node->data);
}
