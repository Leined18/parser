/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-h <mvidal-h@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 10:32:19 by mvidal-h          #+#    #+#             */
/*   Updated: 2025/02/03 10:32:47 by mvidal-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

// Función auxiliar para imprimir los espacios
static void print_spaces(int level)
{
	for (int i = 0; i < level; i++)
		ft_printf("   ");
}

// Función principal para imprimir el árbol binario
int	print_tree(t_mt *root, int level)
{
	if (root == NULL)
	{
		print_spaces(level);
		ft_printf("NULL\n");
		return 0;
	}
	// Imprimir el nodo actual
	print_spaces(level);
	ft_printf("Node: %s (Priority: %d) (state: %d)\n", root->key, root->values.priority, root->values.state);
	if (ft_mtcheck_state(root, PARENTESIS))
		if (!print_tree(root->aux, level))
			return (0);
	// Imprimir hijos izquierdo y derecho
	print_spaces(level);
	ft_printf("Left:\n");
	print_tree(root->vect[LEFT], level + 1);
	print_spaces(level);
	ft_printf("Right:\n");
	print_tree(root->vect[RIGHT], level + 1);
	return (1);
}