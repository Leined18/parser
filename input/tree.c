/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpalac <danpalac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 11:45:03 by danpalac          #+#    #+#             */
/*   Updated: 2024/12/09 12:57:32 by danpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

/**
 * add_node - Adds a node to the binary tree based on operator precedence
 * @root: The root of the binary tree
 * @node: The new node to add
 * Returns: The new root of the binary tree
 */

t_mt	*create_node(char *data)
{
	t_mt	*node;

	node = ft_mtnew(data, ft_strdup(data), STRING);
	if (!node)
		return (NULL);
	return (node);
}

t_mt	*add_node(t_mt *root, t_mt *node)
{
	if (!root)
		return (node);
	if (is_operator_token(node->data, 0) && has_higher_precedence(node->data,
			root->data))
	{
		node->left = root;
		return (node);
	}
	root->right = add_node(root->right, node);
	return (root);
}

t_mt	*create_node_with_children(char *value, t_mt *children)
{
	t_mt	*node;

	// Crear el nodo principal
	node = ft_mtnew(value, NULL, NONE);
	if (!node)
		return (NULL);
	node->left = children;
	// Marcar este nodo como un grupo (opcional)
	return (node);
}
