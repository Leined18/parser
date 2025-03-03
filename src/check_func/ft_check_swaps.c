/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_swaps.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpalac <danpalac@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 08:24:34 by danpalac          #+#    #+#             */
/*   Updated: 2025/03/03 08:35:03 by danpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

/**
 * @brief intercambia los nodos curr y el de la direccion indicada
 *
 */

void	ft_check_swaps(t_mt **tokens)
{
	t_mt *cur;

	if (!tokens || !*tokens)
		return ;
	if (ft_mtcheck_state(*tokens, COMMAND) && need_redirect_swap(*tokens))
		ft_mtswap(tokens, RIGHT);
	cur = *tokens;
	while (cur)
	{
		if (!ft_mtcheck_key(cur, "<"))
		{
			if (cur->vect[LEFT] && ft_mtcheck_state(cur->vect[LEFT], COMMAND))
				ft_mtexchange(tokens, cur, LEFT);
		}
		cur = cur->vect[RIGHT];
	}
}