/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_tree_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpalac <danpalac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 14:41:22 by danpalac          #+#    #+#             */
/*   Updated: 2024/12/20 11:24:46 by danpalac         ###   ########.fr       */
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

t_mt	*find_highest_priority_node(t_mt **tokens)
{
	t_mt	*highest_priority_node;
	t_mt	*current;

	highest_priority_node = NULL;
	current = *tokens;
	if (!tokens || !*tokens)
		return (NULL);
	// Recorre la lista de tokens
	while (current)
	{
		// Si encuentra un nodo de mayor prioridad
		if (!highest_priority_node
			|| get_operator_priority(current) > get_operator_priority(highest_priority_node))
			highest_priority_node = current;
		current = current->vect.right;
	}
	// Si el nodo tiene dependencias, asegúrate de asignarlas
	if (highest_priority_node)
	{
		// Asigna el nodo izquierdo como el nodo anterior
		if (highest_priority_node->vect.back == NULL
			&& highest_priority_node->vect.left)
			highest_priority_node->vect.back = ft_mtsub(tokens,
					highest_priority_node->vect.left);
		// Asigna el nodo derecho como el siguiente
		if (highest_priority_node->vect.front == NULL
			&& highest_priority_node->vect.right)
			highest_priority_node->vect.front = ft_mtsub(tokens,
					highest_priority_node->vect.right);
	}
	return (highest_priority_node);
}
