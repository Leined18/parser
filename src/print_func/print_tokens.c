/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-h <mvidal-h@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 10:31:37 by mvidal-h          #+#    #+#             */
/*   Updated: 2025/02/27 12:37:44 by mvidal-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

void	print_aux_nodes(t_mt *node, int depth)
{
	int	i;
	
	while (node)
	{
		while (i++ < depth)
			ft_printf("      ");
		if (depth > 0)
			ft_printf("  |____[%s(p:%d)(e:%d)(flag:%d)]\n", (char *)(node->data),
				node->values.priority, node->values.state, node->values.boolean);
		else
			ft_printf("[%s(P:%d)(e:%d)(flag:%d)]\n", (char *)(node->data),
				node->values.priority, node->values.state, node->values.boolean);
		if (node->aux)
			print_aux_nodes(node->aux, depth + 1);
		node = node->vect[RIGHT];
	}
}

void	print_tokens(t_mt **tokens)
{
	t_mt *cur;

	if (!tokens || !*tokens)
		return;
	cur = *tokens;
	while (cur)
	{
		ft_printf("[%s(P:%d)(e:%d)(flag:%d)]\n", cur->key, cur->values.priority, cur->values.state, cur->values.boolean);
		if (cur->aux)
			print_aux_nodes(cur->aux, 1);
		cur = cur->vect[RIGHT];
	}
}
