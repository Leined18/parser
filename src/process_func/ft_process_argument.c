/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_argument.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpalac <danpalac@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 12:54:22 by danpalac          #+#    #+#             */
/*   Updated: 2025/03/12 09:52:57 by danpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

static int	is_argument(t_mt *node)
{
	if (!node)
		return (0);
	if (ft_mtcheck_state(node, OPERATOR) || ft_mtcheck_state(node, REDIRECTION)
		|| ft_mtcheck_state(node, PARENTESIS) || ft_mtcheck_state(node,
			COMMAND))
		return (0);
	return (1);
}

static int	is_command(t_mt *node)
{
	if (!node)
		return (0);
	if (ft_mtcheck_state(node, WORD))
		return (1);
	return (0);
}

static t_mt	*set_arguments(t_mt **command)
{
	t_mt	*arg;

	if (!(*command))
		return (NULL);
	arg = (*command)->vect[RIGHT];
	if (is_command((*command)))
	{
		(*command)->values.state = COMMAND;
		while (is_argument(arg))
			ft_mtpush_last(&(*command)->aux, &arg, RIGHT);
		return (*command);
	}
	return (NULL);
}

int	ft_process_argument(t_mt **list)
{
	t_mt	*current;
	t_mt	*command;

	if (!list || !(*list))
		return (0);
	current = *list;
	while (current)
	{
		command = set_arguments(&current);
		if (ft_mtcheck_state(current, REDIRECTION) && !command)
		{
			if (ft_mtcheck_state(current->vect[RIGHT], WORD))
				command = ft_mtsub(&current, current->vect[RIGHT]);
			ft_mtpush_last(&current->aux, &command, RIGHT);
		}
		if (ft_mtcheck_state(current, PARENTESIS))
			ft_process_argument(&current->aux);
		if (current)
			current = current->vect[RIGHT];
	}
	return (1);
}
