/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_parentheses.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpalac <danpalac@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 11:31:09 by danpalac          #+#    #+#             */
/*   Updated: 2025/01/30 11:31:18 by danpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

/**
 * ft_process_parentheses - Handles nested parentheses
 * @input: The input string
 * @i: Pointer to the current index
 * @list: Pointer to the root of the list
 */

int	ft_process_parentheses(char *input, int *i, t_mt **list, char *key)
{
	t_mt	*sublist;
	char	*token;
	t_mt	*new_node;
	int		j;

	sublist = NULL;
	new_node = NULL;
	if (!input || !i || !list)
		return (0);
	token = ft_extract_parentheses_token(input, i);
	if (!token)
		return (0);
	j = 0;
	sublist = ft_tokenize(token, &j); // tokeniza el interior del parentesis
	// Crea y agrega el nodo del paréntesis al árbol principal
	new_node = ft_create_parentheses_node(key, sublist);
	if (!new_node)
		return (0);
	ft_mtaddlast_right(list, new_node);
	return (1);
}
