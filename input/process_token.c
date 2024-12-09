/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpalac <danpalac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 15:52:53 by danpalac          #+#    #+#             */
/*   Updated: 2024/12/09 13:29:59 by danpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

/**
 * process_word - Handles words and non-operator tokens
 * @input: The input string
 * @i: Pointer to the current index
 * @tree: Pointer to the root of the tree
 */
void	process_word(char *input, int *i, t_mt **tree)
{
	char	*token;

	token = extract_word_token(input, i);
	if (token)
	{
		*tree = add_node(*tree, create_node(token));
		free(token);
	}
}

/**
 * process_operator - Handles operators in the input
 * @input: The input string
 * @i: Pointer to the current index
 * @tree: Pointer to the root of the tree
 */
void	process_operator(char *input, int *i, t_mt **tree)
{
	char	*token;

	token = extract_operator_token(input, i);
	if (token)
	{
		*tree = add_node(*tree, create_node(token));
		free(token);
	}
}

/**
 * process_parentheses - Handles nested parentheses
 * @input: The input string
 * @i: Pointer to the current index
 * @tree: Pointer to the root of the tree
 */
void	process_parentheses(char *input, int *i, t_mt **tree)
{
	t_mt	*subtree;

	subtree = NULL;
	(*i)++; // Skip '('
	while (input[*i] && input[*i] != ')')
		process_token(input, i, &subtree);
	if (input[*i] == ')') // Skip ')'
		(*i)++;
	if (subtree)
		*tree = add_node(*tree, create_node_with_children("()", subtree));
}

/**
 * process_token - Identifies the type of token and delegates processing
 * @input: The input string
 * @i: Pointer to the current index
 * @tree: Pointer to the root of the tree
 */
void	process_token(char *input, int *i, t_mt **tree)
{
	if (!i || !input || !tree)
		return ;
	while (is_whitespace(input[*i]))
		(*i)++; // Skip whitespace
	if (input[*i] == '(')
		process_parentheses(input, i, tree);
	else if (is_operator(input[*i]))
		process_operator(input, i, tree);
	else
		process_word(input, i, tree);
}
