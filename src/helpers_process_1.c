/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_process_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpalac <danpalac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/01/28 12:40:24 by danpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

/**
 * ft_process_word - Handles words and non-operator tokens
 * @input: The input string
 * @i: Pointer to the current index
 * @list: Pointer to the root of the list
 */

void	ft_process_sublist(char *input, int *i, t_mt **sublist)
{
	while (input[*i] && input[*i] != ')')
	{
		ft_process_token(input, i, sublist, transition(START, input[*i]));
	}
	if (input[*i] == ')') // Ignora el ')' final
		(*i)++;
}

t_mt	*ft_create_parentheses_node(t_mt *sublist)
{
	t_mt	*new_node;

	new_node = ft_newnode("()", PARENTESIS);
	if (new_node && sublist)
		ft_mtaddlast_aux(new_node, sublist);
	return (new_node);
}

static int	is_argument(t_mt *node)
{
	if (!node)
		return (0);
	if (!ft_mtcheck_state(node, OPERATOR) && !ft_mtcheck_state(node,
			REDIRECTION) && !ft_mtcheck_state(node, PARENTESIS)
		&& !ft_mtcheck_state(node, COMMAND))
		return (1);
	return (0);
}

int	ft_process_argument(t_mt **list)
{
	t_mt	*arg;
	t_mt	*current;
	t_mt	*command;

	if (!list || !(*list))
		return (0);
	current = *list;
	while (current)
	{
		if (is_argument(current))
		{
			command = current;
			command->values.state = COMMAND;
			arg = current->vect[RIGHT];
			while (is_argument(arg))
				ft_mtpush_last(&command->aux, &arg, RIGHT);
			current = arg;
		}
		if (ft_mtcheck_state(current, PARENTESIS))
			ft_process_argument(&current->aux);
		if (current)
			current = current->vect[RIGHT];
	}
	return (1);
}
