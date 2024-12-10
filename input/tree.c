/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpalac <danpalac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 11:45:03 by danpalac          #+#    #+#             */
/*   Updated: 2024/12/10 13:01:32 by danpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

/**
 * add_node - Adds a node to the binary tree based on operator precedence
 * @root: The root of the binary tree
 * @node: The new node to add
 * Returns: The new root of the binary tree
 */

t_mt	*create_node(char *data, e_state state)
{
	t_mt	*node;

	node = ft_mtnew(data, ft_strdup(data), STRING);
	if (!node)
		return (NULL);
	node->values.state = state;
	return (node);
}
