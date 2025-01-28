/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ft_process_utils.c                                 :+:      :+:    :+:
 */
/*                                                    +:+ +:+         +:+     */
/*   By: danpalac <danpalac@student.42madrid.com    +#+  +:+       +#+        */
/*   By: danpalac <danpalac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 15:52:53 by danpalac          #+#    #+#             */
/*   Updated: 2025/01/17 16:01:34 by danpalac         ###   ########.fr       */
/*   Updated: 2025/01/27 11:37:06 by danpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

/**
 * ft_process_word - Handles words and non-operator tokens
 * @input: The input string
 * @i: Pointer to the current index
 * @list: Pointer to the root of the list
 */

int	ft_process_word(char *input, int *i, t_mt **list, e_pstate state)
{
	char	*token;

	if (!input || !i || !list)
		return (0);
	token = ft_extract_word_token(input, i);
	if (!token)
		return (0);
	if (ft_strchr(token, '='))
	{
		ft_mtaddlast_right(list, ft_newnode(token, ASSIGNMENT));
		return (free(token), 1);
	}
	else
		ft_mtaddlast_right(list, ft_newnode(token, state));
	free(token);
	return (1);
}

int	ft_process_quote(char *input, int *i, t_mt **list, e_pstate state)
{
	char	*token;

	if (!input || !i || !list)
		return (0);
	token = ft_extract_quoted_token(input, i);
	if (token)
	{
		ft_mtaddlast_right(list, ft_newnode(token, state));
		free(token);
	}
	return (1);
}

/**
 * ft_process_operator - Handles operators in the input
 * @input: The input string
 * @i: Pointer to the current index
 * @list: Pointer to the root of the list
 */
int	ft_process_operator(char *input, int *i, t_mt **list)
{
	char	*token;

	if (!input || !i || !list)
		return (0);
	token = ft_extract_operator_token(input, i);
	if (token)
	{
		ft_mtaddlast_right(list, ft_newnode(token, OPERATOR));
		free(token);
	}
	return (1);
}

int	ft_process_redirection(char *input, int *i, t_mt **list)
{
	char	*token;

	if (!input || !i || !list)
		return (0);
	token = ft_extract_operator_token(input, i);
	if (token)
	{
		ft_mtaddlast_right(list, ft_newnode(token, REDIRECTION));
		free(token);
	}
	return (1);
}

/**
 * ft_process_parentheses - Handles nested parentheses
 * @input: The input string
 * @i: Pointer to the current index
 * @list: Pointer to the root of the list
 */

int	ft_process_parentheses(char *input, int *i, t_mt **list)
{
	t_mt	*sublist;
	t_mt	*new_node;

	sublist = NULL;
	new_node = NULL;
	if (!input || !i || !list)
		return (0);
	// Avanza para ignorar el '(' inicial
	(*i)++;
	// Procesa tokens dentro de los paréntesis
	ft_process_sublist(input, i, &sublist);
	// Crea y agrega el nodo del paréntesis al árbol principal
	new_node = ft_create_parentheses_node(sublist);
	if (!new_node)
		return (0);
	ft_mtaddlast_right(list, new_node);
	return (1);
}
