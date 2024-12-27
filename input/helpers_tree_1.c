/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_tree_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpalac <danpalac@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 14:41:22 by danpalac          #+#    #+#             */
/*   Updated: 2024/12/27 08:15:08 by danpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

t_mt	*create_node(char *data, e_state state)
{
	t_mt	*node;

	node = ft_mtnew(data, ft_strdup(data), STRING);
	if (!node)
		return (NULL);
	node->values.state = state;
	return (node);
}

// Función para obtener la prioridad de un operador
int	get_operator_priority(t_mt *node)
{
	if (!node || !node->data)
		return (-1);
	// Paréntesis ()
	if (node->values.state == PARENTESIS)
		return (6);
	// Operadores lógicos && y ||
	if (node->values.state == OPERATOR && (ft_strcmp(node->data, "&&") == 0
			|| ft_strcmp(node->data, "||") == 0))
		return (5);
	// Redirección: >, <, >>, 2>, <<<, etc.
	if (node->values.state == REDIRECTION)
		return (4);
	// Tuberías (|) y ejecución en segundo plano (&)
	if (node->values.state == OPERATOR && (ft_strcmp(node->data, "|") == 0
			|| ft_strcmp(node->data, "&") == 0))
		return (3);
	// Comillas dobles (") y simples (')
	if (node->values.state == QUOTE || node->values.state == WORD)
		return (2);
	// Comparación de cadenas y números: =, !=, -eq, -ne, -gt, -lt, -ge, -le
	if (node->values.state == ASSIGNMENT)
		return (1);
	return (0); // Otros operadores o estados
}
