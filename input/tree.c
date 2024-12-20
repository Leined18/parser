/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpalac <danpalac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 11:45:03 by danpalac          #+#    #+#             */
/*   Updated: 2024/12/20 11:08:09 by danpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

/**
 * add_node - Adds a node to the binary tree based on operator precedence
 * @root: The root of the binary tree
 * @node: The new node to add
 * Returns: The new root of the binary tree
 */

// Función para organizar los tokens en un árbol binario por prioridad

t_mt	*add_node(t_mt *root, t_mt *node)
{
	if (!root)
		return (node);
	// Si el nodo actual es operador
	if (node->values.state == REDIRECTION || node->values.state == OPERATOR)
	{
		if (get_operator_priority(node) > get_operator_priority(root))
		{
			node->vect.left = root;
			return (node);
		}
		else
		{
			root->vect.right = add_node(root->vect.right, node);
		}
	}
	return (root);
}
t_mt	*build_binary_tree(t_mt **tokens)
{
	t_mt	*tree;
	t_mt	*current_node;

	tree = NULL;
	while (*tokens)
	{
		// Extraer nodo con prioridad más alta
		current_node = find_highest_priority_node(tokens);
		ft_mtsub(tokens, current_node);
		// Insertar en el árbol binario
		tree = add_node(tree, current_node);
	}
	return (tree);
}
