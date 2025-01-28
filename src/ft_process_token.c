/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_token.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpalac <danpalac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 10:54:30 by danpalac          #+#    #+#             */
/*   Updated: 2025/01/27 16:50:47 by danpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

/**
 * process_token - Identifies the type of token and delegates processing
 * @input: The input string
 * @i: Pointer to the current index
 * @tree: Pointer to the root of the list
 */
int	ft_process_token(char *input, int *i, t_mt **list, e_pstate state)

int	process_token(char *input, int *i, t_mt **list, e_state state)
{
	if (!i || !input || !list)
		return (0);
	if (input[*i] == '(')
		ft_process_parentheses(input, i, list);
	else if (state == WORD || state == ARGUMENT)
		process_word(input, i, list, state);
	else if (state == SINGLE_QUOTE || state == DOUBLE_QUOTE)
		process_quote(input, i, list, state);
	else if (state == OPERATOR)
		ft_process_operator(input, i, list);
	else if (state == REDIRECTION)
		process_redirection(input, i, list);
	else if (state == EXPANSION)
		process_word(input, i, list, state);
	else
		(*i)++;
	return (1);
}
