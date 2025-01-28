/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_process_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpalac <danpalac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/01/28 08:48:31 by danpalac         ###   ########.fr       */
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

int	ft_process_argument(t_mt **list)
{
	if (!list)
		return (0);
	return (1);
}
