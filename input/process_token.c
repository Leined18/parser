/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpalac <danpalac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 15:52:53 by danpalac          #+#    #+#             */
/*   Updated: 2024/12/11 11:45:12 by danpalac         ###   ########.fr       */
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
		ft_mtadd_back(tree, create_node(token, WORD));
		free(token);
	}
}

void	process_option(char *input, int *i, t_mt **tree)
{
	char	*token;

	token = extract_word_token(input, i);
	if (token)
	{
		ft_mtadd_back(tree, create_node(token, OPTIONS));
		free(token);
	}
}

void	process_quote(char *input, int *i, t_mt **tree)
{
	char	*token;

	token = extract_quoted_token(input, i);
	if (token)
	{
		ft_mtadd_back(tree, create_node(token, QUOTE));
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
		ft_mtadd_back(tree, create_node(token, OPERATOR));
		free(token);
	}
}

void	process_redirection(char *input, int *i, t_mt **tree)
{
	char	*token;

	token = extract_operator_token(input, i);
	if (token)
	{
		ft_mtadd_back(tree, create_node(token, REDIRECTION));
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
	t_mt	*new_node;

	subtree = NULL;
	(*i)++;
	while (input[*i] && input[*i] != ')')
		process_token(input, i, &subtree, transition(START, input[*i]));
	if (input[*i] == ')') // Skip ')'
		(*i)++;
	new_node = create_node("()", PARENTESIS);
	if (subtree)
		ft_mtadd_child(new_node, subtree);
	ft_mtadd_back(tree, new_node);
}

/**
 * process_token - Identifies the type of token and delegates processing
 * @input: The input string
 * @i: Pointer to the current index
 * @tree: Pointer to the root of the tree
 */
void	process_token(char *input, int *i, t_mt **tree, e_state state)
{
	if (!i || !input || !tree)
		return ;
	if (input[*i] == '(')
		process_parentheses(input, i, &(*tree));
	else if (state == WORD)
		process_word(input, i, &(*tree));
	else if (state == QUOTE)
		process_quote(input, i, &(*tree));
	else if (state == OPERATOR)
		process_operator(input, i, &(*tree));
	else if (state == REDIRECTION)
		process_redirection(input, i, &(*tree));
	else
		(*i)++;
}
