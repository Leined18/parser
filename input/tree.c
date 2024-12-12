/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpalac <danpalac@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 11:45:03 by danpalac          #+#    #+#             */
/*   Updated: 2024/12/12 15:18:48 by danpalac         ###   ########.fr       */
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

t_mt	*ft_mtfirst(t_mt *list)
{
	if (!list)
		return (NULL);
	while (list->left)
		list = list->left;
	return (list);
}

t_mt *ft_mtfirst_parent(t_mt *list)
{
	if (!list)
		return (NULL);
	while (list->parent)
		list = list->parent;
	return (list);
}

t_mt	*tree_by_priority(t_mt **tokens)
{
	t_mt	*highest_priority_node;
	t_mt	*new_tree;

	highest_priority_node = NULL;
	new_tree = NULL;
	if (!*tokens)
		return (NULL);
	highest_priority_node = find_highest_priority_node(*tokens);
	if (highest_priority_node)
	{
		if (!new_tree)
			ft_mtpush(&highest_priority_node, &new_tree);
		ft_mtpush(&highest_priority_node, &new_tree->left);
		ft_mtpush(&highest_priority_node, &new_tree->right);
		tree_by_priority(&highest_priority_node);
	}
	*tokens = new_tree;
	return (new_tree);
}
