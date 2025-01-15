/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpalac <danpalac@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 15:52:53 by danpalac          #+#    #+#             */
/*   Updated: 2025/01/15 19:02:59 by danpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

/**
 * process_word - Handles words and non-operator tokens
 * @input: The input string
 * @i: Pointer to the current index
 * @list: Pointer to the root of the list
 */

int	process_word(char *input, int *i, t_mt **list, e_state state)
{
	char	*token;

	if (!input || !i || !list)
		return (0);
	token = extract_word_token(input, i);
	if (token)
	{
		if (state == ARGUMENT)
			ft_mtaddlast_aux(ft_mtlast(*list, RIGHT), create_node(token, ARGUMENT));
		else if (state == WORD)
		{
			if (ft_strchr(token, '='))
			{
				ft_mtaddlast_right(list, create_node(token, ASSIGNMENT));
				return (free(token), 1);
			}
			else
				ft_mtaddlast_right(list, create_node(token, WORD));
			process_argument(input, i, list);
		}
		free(token);
	}
	return (1);
}

int	process_quote(char *input, int *i, t_mt **list, e_state state)
{
	char	*token;

	if (!input || !i || !list)
		return (0);
	token = extract_quoted_token(input, i);
	if (token)
	{
		if (state == ARGUMENT)
		{
			ft_mtaddlast_aux(ft_mtlast(*list, RIGHT), create_node(token, ARGUMENT));
			free(token);
			return (1);
		}
		else if (state == SINGLE_QUOTE || state == DOUBLE_QUOTE)
		{
			ft_mtaddlast_right(list, create_node(token, state));
			process_argument(input, i, list);
		}
		free(token);
	}
	return (1);
}

/**
 * process_operator - Handles operators in the input
 * @input: The input string
 * @i: Pointer to the current index
 * @list: Pointer to the root of the list
 */
int	process_operator(char *input, int *i, t_mt **list)
{
	char	*token;

	if (!input || !i || !list)
		return (0);
	token = extract_operator_token(input, i);
	if (token)
	{
		ft_mtaddlast_right(list, create_node(token, OPERATOR));
		free(token);
	}
	return (1);
}

int	process_redirection(char *input, int *i, t_mt **list)
{
	char	*token;

	if (!input || !i || !list)
		return (0);
	token = extract_operator_token(input, i);
	if (token)
	{
		ft_mtaddlast_right(list, create_node(token, REDIRECTION));
		free(token);
	}
	return (1);
}

/**
 * process_parentheses - Handles nested parentheses
 * @input: The input string
 * @i: Pointer to the current index
 * @list: Pointer to the root of the list
 */

int	process_parentheses(char *input, int *i, t_mt **list)
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
	process_sublist(input, i, &sublist);
	// Crea y agrega el nodo del paréntesis al árbol principal
	new_node = create_parentheses_node(sublist);
	if (!new_node)
		return (0);
	ft_mtaddlast_right(list, new_node);
	return (1);
}
