/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_priority.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpalac <danpalac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 09:41:59 by danpalac          #+#    #+#             */
/*   Updated: 2024/12/30 12:04:12 by danpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

/**
 * @brief  funcion para establecer la
 * prioridad de cada nodo de una lista segun lo que devuelve func
 *
 * @param list lista de nodos
 * @param func devuelve el numero de prioridad
 */

void	ft_set_priority(t_mt *list, void *param, void (*func)(t_mt *, void *))
{
	if (!list || !func)
		return ;
	ft_mtiter(list, param, func);
}

int	get_priority(char *str)
{
	if (!str)
		return (-1);
	if (!ft_strcmp(str, "()"))
		return (0);
	else if (!ft_strcmp(str, "&&") || !ft_strcmp(str, "||"))
		return (1);
	else if (!ft_strncmp(str, ">", 1) || !ft_strncmp(str, "<", 1))
		return (2);
	else if (!ft_strcmp(str, "|") || !ft_strcmp(str, "&"))
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
