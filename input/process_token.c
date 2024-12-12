/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpalac <danpalac@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 10:54:30 by danpalac          #+#    #+#             */
/*   Updated: 2024/12/12 12:20:39 by danpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

/**
 * process_token - Identifies the type of token and delegates processing
 * @input: The input string
 * @i: Pointer to the current index
 * @tree: Pointer to the root of the tree
 */
int	process_token(char *input, int *i, t_mt **tree, e_state state)
{
	if (!i || !input || !tree)
		return (0);
	if (input[*i] == '(')
		process_parentheses(input, i, tree);
	else if (state == WORD || state == ARGUMENT)
		process_word(input, i, tree, state);
	else if (state == QUOTE)
		process_quote(input, i, tree, state);
	else if (state == OPERATOR)
		process_operator(input, i, tree);
	else if (state == REDIRECTION)
		process_redirection(input, i, tree);
	else
		(*i)++;
	return (1);
}
