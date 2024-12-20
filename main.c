/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpalac <danpalac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 01:12:30 by danpalac          #+#    #+#             */
/*   Updated: 2024/12/20 13:12:40 by danpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

/**
 * parser - Main parser function to create a hash table and organize input
 * @input: The input string
 * Returns: A hash table with the parsed data
 */

void	print_state(t_mt *list, void *a)
{
	(void)a;
	printf("key: %s\n", (char *)list->key);
	printf("Data: %s\n", (char *)list->data);
	printf("State: %d\n", list->values.state);
}

int	ft_execute_tree(t_mt *tree, int (*func)(t_mt *node, t_mt *aux))
{
	if (!tree)
		return (0);
	if (tree->vect.left)
		ft_execute_tree(tree->vect.left, func);
	if (tree->vect.right)
		ft_execute_tree(tree->vect.right, func);
	return (func(tree, tree->aux));
}

int	ft_execute(t_mt *tree, t_mt *aux)
{
	if (!tree)
		return (0);
	(void)aux;
	printf("Data: %s\n", (char *)tree->data);
	return (1);
}

int	main(void)
{
	char	*input;
	t_mt	*list;

	input = get_next_line(0);
	input[ft_strlen(input) - 1] = '\0';
	list = NULL;
	list = parse_input(input);
	if (!list)
	{
		free(input);
		ft_error("Error\n", 1);
		return (1);
	}
	// list = build_binary_tree(&list); // falta implementar
	// ft_execute_tree(list, ft_execute);
	ft_mtclear(&list);
	free(input);
	ft_successful("Success\n", 1);
	return (0);
}

/* t_hash_table	*parser(char *input)
{
	t_hash_table	*ptable;
	t_mt			*tree;

	if (!input)
		return (NULL);
	ptable = ft_mthash_new_table(3, "parser");
	if (!ptable)
		return (NULL);
	tree = tokenize(input);
	parse_input(input);
	if (!tree)
	{
		ft_mthash_table_free((void **)&ptable);
		return (NULL);
	}
	ptable->methods.add_child(ptable, "tree", tree);
	return (ptable);
} */