/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_check_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpalac <danpalac@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 09:58:40 by danpalac          #+#    #+#             */
/*   Updated: 2025/03/10 10:22:23 by danpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	ft_check_parentesis_mt(t_mt *op, int *error)
{
	if (!op)
		return (1);
	if (!op->aux)
		return (*(int *)error = 1, ft_printf(SYNTAX_ERROR, ")"), 1);
	if (ft_mtcheck_state(op->vect[RIGHT], PARENTESIS))
		return (*(int *)error = 1, ft_printf(SYNTAX_ERROR, "("), 1);
	if (ft_mtcheck_state(op->vect[LEFT], PARENTESIS))
		return (*(int *)error = 1, ft_printf(SYNTAX_ERROR, "()"), 1);
	if (!ft_mtcheck_state(op->vect[LEFT], OPERATOR))
	{
		if (op->vect[LEFT] && op->vect[LEFT]->values.boolean)
			return (*(int *)error = 1, ft_printf(SYNTAX_ERROR, "("), 1);
	}
	return (0);
}
