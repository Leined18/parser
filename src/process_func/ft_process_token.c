/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_token.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpalac <danpalac@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 10:54:30 by danpalac          #+#    #+#             */
/*   Updated: 2025/03/10 08:52:42 by danpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

/**
 * process_token - Identifies the type of token and delegates processing
 * @input: The input string
 * @i: Pointer to the current index
 * @tree: Pointer to the root of the list
 */

static int	ft_skip(t_mt *list, int *i)
{
	if (!list)
		return ((*i)++, 1);
	(*i)++;
	ft_mtlast(list, RIGHT)->values.boolean = TRUE;
	return (1);
}

int	ft_process_token(char *input, int *i, t_mt **list, t_pstate state)
{
	if (!i || !input || !list)
		return (0);
	if (state == PARENTESIS)
		ft_process_parentheses(input, i, list, "()");
	else if (state == WORD || state == WILDCARD)
		ft_process_word(input, i, list, state);
	else if (state == SINGLE_QUOTE || state == DOUBLE_QUOTE)
		ft_process_quote(input, i, list, state);
	else if (state == OPERATOR)
		ft_process_operator(input, i, list);
	else if (state == REDIRECTION)
		ft_process_redirection(input, i, list);
	else if (state == EXPANSION)
		ft_process_expantion(input, i, list);
	else
		return (ft_skip(*list, i));
	return (1);
}
