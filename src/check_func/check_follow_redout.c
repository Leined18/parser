/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_follow_redout.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpalac <danpalac@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 11:38:14 by mvidal-h          #+#    #+#             */
/*   Updated: 2025/03/12 09:44:10 by danpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

/*It checks if node is a redirection. Return 1 if it is, 0 if it is not*/
static int	is_redout(t_mt *cur)
{
	if (!cur)
		return (0);
	if (!ft_mtcheck_key(cur, ">") || !ft_mtcheck_key(cur, ">>"))
		return (1);
	return (0);
}

/*It checks if there are two or more followed output redirections and exchange 
firt with last*/
void	check_follow_redout(t_mt **token)
{
	t_mt	*cur;
	t_mt	*last;
	t_mt	*first;

	if (!token || !*token)
		return ;
	cur = *token;
	first = NULL;
	last = NULL;
	while (cur && !last)
	{
		if (is_redout(cur))
		{
			if (!first)
				first = cur;
			if (!is_redout(cur->vect[RIGHT]))
				last = cur;
		}
		cur = cur->vect[RIGHT];
	}
	if (first && last && first != last)
		ft_mtexchange_nodes(token, first, last);
}
