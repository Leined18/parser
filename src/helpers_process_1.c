/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_process_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpalac <danpalac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/01/27 17:04:06 by danpalac         ###   ########.fr       */
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

int	ft_process_argument(char *input, int *i, t_mt **list)
{
	e_pstate	state;

	if (!input || !i || !list)
		return (0);
	state = START;
	state = ARGUMENT;
	state = transition(state, input[*i]);
	while (state != OPERATOR && state != REDIRECTION && state != END
		&& state != PARENTESIS)
	{
		if (state == WORD)
			process_word(input, i, list, ARGUMENT);
		if (state == EXPANSION)
			process_word(input, i, list, EXPANSION);
		if (state == SINGLE_QUOTE || state == DOUBLE_QUOTE)
			process_quote(input, i, list, state);
		state = transition(state, input[*i]);
		if (state == START)
			(*i)++;
	}
	return (1);
}
