/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mtexchange_nodes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-h <mvidal-h@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 18:42:48 by mvidal-h          #+#    #+#             */
/*   Updated: 2025/03/07 18:51:53 by mvidal-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h" 

//EN PROCESO CON ERRORES
void	ft_update_neighbors(t_mt *prev, t_mt *next, t_mt *new_mid)
{
	if (prev)
		prev->vect[RIGHT] = new_mid;
	if (next)
		next->vect[LEFT] = new_mid;
}

void	ft_swap_adjacent(t_mt *first, t_mt *last)
{
	ft_update_neighbors(first->vect[LEFT], last->vect[RIGHT], last);
	last->vect[RIGHT] = first;
	first->vect[LEFT] = last;
	first->vect[RIGHT] = last->vect[RIGHT];
	last->vect[LEFT] = first->vect[LEFT];
}

void	ft_swap_general(t_mt *first, t_mt *last)
{
	t_mt	*temp_left;
	t_mt	*temp_right;

	temp_left = first->vect[LEFT];
	temp_right = first->vect[RIGHT];
	ft_update_neighbors(temp_left, last->vect[RIGHT], last);
	ft_update_neighbors(last->vect[LEFT], temp_right, first);
	first->vect[LEFT] = last->vect[LEFT];
	first->vect[RIGHT] = last->vect[RIGHT];
	last->vect[LEFT] = temp_left;
	last->vect[RIGHT] = temp_right;
}

void	ft_mtexchange_nodes(t_mt **token, t_mt *first, t_mt *last)
{
	if (!token || !*token || !first || !last || first == last)
		return;
	if (first->vect[RIGHT] == last)
		ft_swap_adjacent(first, last);
	else if (last->vect[RIGHT] == first)
		ft_swap_adjacent(last, first);
	else
		ft_swap_general(first, last);
	if (*token == first)
		*token = last;
	else if (*token == last)
		*token = first;
}
