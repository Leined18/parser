/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpalac <danpalac@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 10:32:19 by mvidal-h          #+#    #+#             */
/*   Updated: 2025/02/24 12:53:22 by danpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

static void	print_spaces(int level)
{
	int	i;

	i = -1;
	while (++i < level)
		ft_printf("   ");
}

int	print_tree(t_mt *root, int level)
{
	if (root == NULL)
	{
		print_spaces(level);
		ft_printf("NULL\n");
		return (0);
	}
	print_spaces(level);
	ft_printf("Node: %s (Priority: %d) (state: %d)\n", root->key,
		root->values.priority, root->values.state);
	if (ft_mtcheck_state(root, PARENTESIS))
		if (!print_tree(root->aux, level))
			return (0);
	print_spaces(level);
	ft_printf("Left:\n");
	print_tree(root->vect[LEFT], level + 1);
	print_spaces(level);
	ft_printf("Right:\n");
	print_tree(root->vect[RIGHT], level + 1);
	return (1);
}
