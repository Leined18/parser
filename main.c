/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpalac <danpalac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 01:12:30 by danpalac          #+#    #+#             */
/*   Updated: 2025/01/27 12:05:58 by danpalac         ###   ########.fr       */
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
	if (!list)
		return ;
	printf("\n");
	printf("key: %s\n", (char *)list->key);
	printf("Data: %p\n", (list->data));
	printf("State: %d\n", list->values.state);
}

void	print_elements(t_mt *node, int depth)
{
	while (node)
	{
		for (int i = 1; i < depth; i++)
			ft_printf("      ");
		if (depth > 0)
			ft_printf("  |____[%p]\n", (node->key));
		else
			ft_printf("[%p]\n", (node->key));
		if (node->aux)
			print_elements(node->aux, depth + 1);
		node = node->vect[RIGHT];
	}
}

int	main(void)
{
	char	*input;
	t_mt	*list;

	input = get_next_line(0);
	input[ft_strlen(input) - 1] = '\0';
	list = NULL;
	list = ft_parse_input(input);
	if (!list)
	{
		free(input);
		ft_error("Error\n", 1);
		return (1);
	}
	ft_mtiter(list, NULL, print_state);
	printf("\n");
	print_elements(list, 0);
	printf("\n");
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