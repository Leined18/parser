/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpalac <danpalac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 15:52:53 by danpalac          #+#    #+#             */
/*   Updated: 2024/12/11 15:30:00 by danpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

/**
 * process_word - Handles words and non-operator tokens
 * @input: The input string
 * @i: Pointer to the current index
 * @tree: Pointer to the root of the tree
 */
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
		state = transition(state, input[*i]);
		if (state == START)
			(*i)++;
	}
	return (1);
}

int	process_word(char *input, int *i, t_mt **tree, e_state state)
{
	char	*token;

	if (!input || !i || !tree)
		return (0);
	token = extract_word_token(input, i);
	if (token)
	{
		if (state == ARGUMENT)
			ft_mtadd_child(ft_mtlast(*tree), create_node(token, ARGUMENT));
		else if (state == WORD)
		{
			ft_mtadd_back(tree, create_node(token, WORD));
			process_argument(input, i, tree);
		}
		free(token);
	}
	return (1);
}

int	process_quote(char *input, int *i, t_mt **tree)
{
	char	*token;

	if (!input || !i || !tree)
		return (0);
	token = extract_quoted_token(input, i);
	if (token)
	{
		ft_mtadd_back(tree, create_node(token, QUOTE));
		free(token);
	}
	return (1);
}

/**
 * process_operator - Handles operators in the input
 * @input: The input string
 * @i: Pointer to the current index
 * @tree: Pointer to the root of the tree
 */
int	process_operator(char *input, int *i, t_mt **tree)
{
	char	*token;

	if (!input || !i || !tree)
		return (0);
	token = extract_operator_token(input, i);
	if (token)
	{
		ft_mtadd_back(tree, create_node(token, OPERATOR));
		free(token);
	}
	return (1);
}

int	process_redirection(char *input, int *i, t_mt **tree)
{
	char	*token;

	if (!input || !i || !tree)
		return (0);
	token = extract_operator_token(input, i);
	if (token)
	{
		ft_mtadd_back(tree, create_node(token, REDIRECTION));
		free(token);
	}
	return (1);
}

/**
 * process_parentheses - Handles nested parentheses
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
		ft_mtadd_child(new_node, subtree);
	return (new_node);
}

int	process_parentheses(char *input, int *i, t_mt **tree)
{
	t_mt	*subtree;
	t_mt	*new_node;

	subtree = NULL;
	new_node = NULL;
	if (!input || !i || !tree)
		return (0);
	// Avanza para ignorar el '(' inicial
	(*i)++;
	// Procesa tokens dentro de los paréntesis
	process_subtree(input, i, &subtree);
	// Crea y agrega el nodo del paréntesis al árbol principal
	new_node = create_parentheses_node(subtree);
	if (!new_node)
		return (0);
	ft_mtadd_back(tree, new_node);
	return (1);
}

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
		process_quote(input, i, tree);
	else if (state == OPERATOR)
		process_operator(input, i, tree);
	else if (state == REDIRECTION)
		process_redirection(input, i, tree);
	else
		(*i)++;
	return (1);
}