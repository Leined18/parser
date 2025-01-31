/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_process_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpalac <danpalac@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/01/31 14:44:55 by danpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

static int	is_argument(t_mt *node)
{
	if (!node)
		return (0);
	if (!ft_mtcheck_state(node, OPERATOR) && !ft_mtcheck_state(node,
			REDIRECTION) && !ft_mtcheck_state(node, PARENTESIS)
		&& !ft_mtcheck_state(node, COMMAND) && !ft_mtcheck_state(node,
			EXPANSION) && !ft_mtcheck_state(node, ASSIGNMENT))
		return (1);
	return (0);
}

static int	set_arguments(t_mt **command)
{
	t_mt	*arg;

	if (!(*command))
		return (0);
	arg = (*command)->vect[RIGHT];
	if (is_argument((*command)))
	{
		(*command)->values.state = COMMAND;
		while (is_argument(arg))
			ft_mtpush_last(&(*command)->aux, &arg, RIGHT);
	}
	return (1);
}

int	ft_process_argument(t_mt **list)
{
	t_mt	*current;

	if (!list || !(*list))
		return (0);
	current = *list;
	while (current)
	{
		if (!set_arguments(&current))
			return (1);
		if (ft_mtcheck_state(current, PARENTESIS))
			ft_process_argument(&current->aux);
		if (current)
			current = current->vect[RIGHT];
	}
	return (1);
}
