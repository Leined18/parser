/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_process_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpalac <danpalac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 10:50:11 by danpalac          #+#    #+#             */
/*   Updated: 2024/12/30 12:16:59 by danpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

/**
 * process_word - Handles words and non-operator tokens
 * @input: The input string
 * @i: Pointer to the current index
 * @list: Pointer to the root of the list
 */

void	process_sublist(char *input, int *i, t_mt **sublist)
{
	while (input[*i] && input[*i] != ')')
	{
		process_token(input, i, sublist, transition(START, input[*i]));
	}
	if (input[*i] == ')') // Ignora el ')' final
		(*i)++;
}

t_mt	*create_parentheses_node(t_mt *sublist)
{
	t_mt	*new_node;

	new_node = create_node("()", PARENTESIS);
	if (new_node && sublist)
		ft_mtadd_aux(new_node, sublist);
	return (new_node);
}

int	process_argument(char *input, int *i, t_mt **list)
{
	e_state	state;

	if (!input || !i || !list)
		return (0);
	state = START;
	state = transition(state, input[*i]);
	while (state != OPERATOR && state != REDIRECTION && state != END
		&& state != PARENTESIS)
	{
		if (state == WORD)
			process_word(input, i, list, ARGUMENT);
		if (state == QUOTE)
			process_quote(input, i, list, ARGUMENT);
		state = transition(state, input[*i]);
		if (state == START)
			(*i)++;
	}
	return (1);
}
