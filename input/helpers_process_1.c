/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_process_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpalac <danpalac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 10:50:11 by danpalac          #+#    #+#             */
/*   Updated: 2024/12/20 11:35:29 by danpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

/**
 * process_word - Handles words and non-operator tokens
 * @input: The input string
 * @i: Pointer to the current index
 * @tree: Pointer to the root of the tree
 */

void	process_subtree(char *input, int *i, t_mt **subtree)
{
	while (input[*i] && input[*i] != ')')
	{
		process_token(input, i, subtree, transition(START, input[*i]));
	}
	if (input[*i] == ')') // Ignora el ')' final
		(*i)++;
}

t_mt	*create_parentheses_node(t_mt *subtree)
{
	t_mt	*new_node;

	new_node = create_node("()", PARENTESIS);
	if (new_node && subtree)
		ft_mtadd_aux(new_node, subtree);
	return (new_node);
}

int	process_argument(char *input, int *i, t_mt **tree)
{
	e_state	state;

	if (!input || !i || !tree)
		return (0);
	state = START;
	state = transition(state, input[*i]);
	while (state != OPERATOR && state != REDIRECTION && state != END
		&& state != PARENTESIS)
	{
		if (state == WORD)
			process_word(input, i, tree, ARGUMENT);
		if (state == QUOTE)
			process_quote(input, i, tree, ARGUMENT);
		state = transition(state, input[*i]);
		if (state == START)
			(*i)++;
	}
	return (1);
}
