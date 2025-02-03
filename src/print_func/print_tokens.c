/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-h <mvidal-h@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 10:31:37 by mvidal-h          #+#    #+#             */
/*   Updated: 2025/02/03 11:26:14 by mvidal-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

void	print_tokens(t_mt *node, int depth)
{
	int	i;

	i = 1;
	while (node)
	{
		while (i++ < depth)
			ft_printf("      ");
		if (depth > 0)
			ft_printf("  |____[%s(p:%d)(e:%d)]\n", (char *)(node->data), node->values.priority, node->values.state);
		else
			ft_printf("[%s(P:%d)(e:%d)]\n", (char *)(node->data), node->values.priority, node->values.state);
		if (node->aux)
			print_tokens(node->aux, depth + 1);
		node = node->vect[RIGHT];
	}
}
